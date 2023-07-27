#include <llapi/LoggerAPI.h>
#include <llapi/EventAPI.h>
#include <llapi/mc/Player.hpp>
#include <llapi/ScheduleAPI.h>

#include "version.h"

#include <cmath>
#include <iostream>
#include <fstream>

extern Logger logger;

std::ofstream dataFile("data/data.desktop.horion.csv");


void CollectorInit()
{

    Event::PlayerAttackEvent::subscribe([](const Event::PlayerAttackEvent& ev) {

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

        if (dataFile.is_open())
        {
            dataFile << std::to_string(playerEntityDir.length()) << "," << std::to_string(angle) + "\n";
        }

        return true;
        });
    Event::ServerStoppedEvent::subscribe([](const Event::ServerStoppedEvent& ev) {
        dataFile.close();
        return true;
        });

}
