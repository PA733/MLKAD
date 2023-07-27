#include <llapi/LoggerAPI.h>
#include <llapi/EventAPI.h>
#include <llapi/mc/Player.hpp>
#include <llapi/ScheduleAPI.h>

#include "version.h"

#include <Nlohmann/json.hpp>

#include <cmath>

using json = nlohmann::json;
json playerAngleData = json::object();
json checkCount = json::object();

extern Logger logger;
int CheckDataInterval = 20;

double targetAbnormalAnglePercentage = 0.2;
double targetAngle = 1.0;

void CheckPlayerData(Player* player)
{
    int abnormalAngleCount = 0;
    int targetAbnormalAngleCount = CheckDataInterval * targetAbnormalAnglePercentage;
    for (int i = 0; i < CheckDataInterval; ++i)
    {
        if(playerAngleData[player->getUuid()][i] > targetAngle)
            ++abnormalAngleCount;
	}
    // 如果average在[targetAverage - averageTolerance, targetAverage + averageTolerance]间
    // 并且standardDeviation在[targetStandardDeviation - standardDeviationTolerance, targetStandardDeviation + standardDeviationTolerance]间
    if (abnormalAngleCount > targetAbnormalAngleCount) {
		logger.error(player->getName() + " may using Kill Aura!");
        logger.info("abnormalAngleCount: " + std::to_string(abnormalAngleCount));
	}
    else {
		/*logger.warn(player->getName() + " may not using Kill Aura!");
        logger.info("abnormalAngleCount: " + std::to_string(abnormalAngleCount));*/
	}
	playerAngleData[player->getUuid()] = json::array();
    checkCount[player->getUuid()] = 0;
}

void DetectorInit()
{

    Event::PlayerAttackEvent::subscribe([](const Event::PlayerAttackEvent& ev) {
        if (playerAngleData.find(ev.mPlayer->getUuid()) == playerAngleData.end())
        {
			playerAngleData[ev.mPlayer->getUuid()] = json::array();
		}
        if (checkCount.find(ev.mPlayer->getUuid()) == checkCount.end())
        {
            checkCount[ev.mPlayer->getUuid()] = 0;
        }
        checkCount[ev.mPlayer->getUuid()] = checkCount[ev.mPlayer->getUuid()] + 1;

        //logger.debug(ev.mPlayer->getUuid() + " attacked " + ev.mTarget->getEntityLocNameString() + "!");
        
        Vec3 playerEyeLoc = ev.mPlayer->getCameraPos();
        //logger.debug("playerEyeLoc: x:" + std::to_string(playerEyeLoc.x) + " y:" + std::to_string(playerEyeLoc.y) + " z:" + std::to_string(playerEyeLoc.z));

        /*Vec3 playerLoc = ev.mPlayer->getPos();
        //logger.debug("playerLoc: x:" + std::to_string(playerLoc.x) + " y:" + std::to_string(playerLoc.y) + " z:" + std::to_string(playerLoc.z));*/

        Vec3 entityLoc = ev.mTarget->getPos();
        //logger.debug("entityLoc: x:" + std::to_string(entityLoc.x) + " y:" + std::to_string(entityLoc.y) + " z:" + std::to_string(entityLoc.z));

        Vec3 playerLookDir = ev.mPlayer->getHeadLookVector(1.0);
        //logger.debug("playerLookDir: x:" + std::to_string(playerLookDir.x) + " y:" + std::to_string(playerLookDir.y) + " z:" + std::to_string(playerLookDir.z));

        // 计算玩家和实体之间的向量，即玩家眼睛位置到实体位置的向量
        Vec3 playerEntityDir = entityLoc - playerEyeLoc;
        //logger.debug("playerEntityDir: x:" + std::to_string(playerEntityDir.x) + " y:" + std::to_string(playerEntityDir.y) + " z:" + std::to_string(playerEntityDir.z));

        // 计算玩家朝向向量和玩家实体向量之间的夹角
        double angle = Vec3::angle(playerLookDir, playerEntityDir);

        playerAngleData[ev.mPlayer->getUuid()].push_back(angle);

        if (checkCount[ev.mPlayer->getUuid()] >= CheckDataInterval) {
            Schedule::delay([player = ev.mPlayer]() {
				CheckPlayerData(player);
				}, 1);
        }


        return true;
        });

}
