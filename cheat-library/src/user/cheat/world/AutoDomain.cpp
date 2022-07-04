#include "pch-il2cpp.h"
#include "AutoDomain.h"

#include <helpers.h>
#include <cheat/game/EntityManager.h>
#include <cheat/events.h>


namespace cheat::feature
{
    AutoDomain::AutoDomain() : Feature(),
        NF(f_Enabled, "Auto Domain", "AutoDomain", false),
        NF(f_Delay, "Delay Between Each Stage", "AutoDomain", 5000),
        StageDelay(0)
    {
        events::GameUpdateEvent += MY_METHOD_HANDLER(AutoDomain::OnGameUpdate);
    }

    const FeatureGUIInfo& AutoDomain::GetGUIInfo() const
    {
        static const FeatureGUIInfo info{ "Auto Domain", "World", true };
        return info;
    }

    void AutoDomain::DrawMain()
    {
        ConfigWidget("Enabled", f_Enabled);
        ConfigWidget(f_Delay, 1, 5, 25, "Adjust this when key loads too late");
    }

    bool AutoDomain::NeedStatusDraw() const
    {
        return f_Enabled;
    }

    void AutoDomain::DrawStatus()
    {
        ImGui::Text("AutoDomain ONGOING");
    }

    AutoDomain& AutoDomain::GetInstance()
    {
        static AutoDomain instance;
        return instance;
    }

    static void Teleport(const app::Vector3& value)
    {
        cheat::game::EntityManager& manager = game::EntityManager::instance();
        cheat::game::Entity* avatarEntity = manager.avatar();
        if (avatarEntity->moveComponent() == nullptr)
            return;
        app::Rigidbody* rigidBody = avatarEntity->rigidbody();
        avatarEntity->setRelativePosition(value);
    }

    static game::Entity* FindRewardTree()
    {
        cheat::game::EntityManager& manager = game::EntityManager::instance();
        for (auto& entity : manager.entities())
        {
            if (entity->name().find("RewardTree") != std::string::npos)
                return entity;
        }
        LOG_DEBUG("No RewardTree found");
        return nullptr;
    }

    auto lerp = [](const app::Vector3 &a, const app::Vector3 &b, float t)
    {
        return app::Vector3{
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t,
            a.z + (b.z - a.z) * t};
    };

    static void Interpolate(app::Vector3 endPos, int delay)
    {
        cheat::game::EntityManager &manager = game::EntityManager::instance();
        app::Vector3 avatarpos = manager.avatar()->absolutePosition();
        std::thread interpolate([avatarpos, endPos, &manager, delay]()
                                {
                float elapsed = 0.0f;
                app::Vector3 speed,newPos = { 0,0,0 };
                while (elapsed <= 1.0f) {
                    newPos = lerp(avatarpos, endPos, elapsed);
                    manager.avatar()->setAbsolutePosition(newPos);
                    elapsed += 0.01f;
                    speed = (newPos - avatarpos);
                    Sleep(delay);
                    if (elapsed >= 1.0f) break;
                } });
        interpolate.detach();
    }

    void AutoDomain::OnGameUpdate()
    {
        if (!f_Enabled)
            return;

        int64_t currentTime = util::GetCurrentTimeMillisec();
        if (currentTime < StageDelay)
            return;

        else if (Stage == 1)
        {
            LOG_INFO("Hello from Stage %i", Stage);

            app::GameObject *DungeonOperator = app::GameObject_Find(string_to_il2cppi("/EffectPool/Eff_Gear_ElementDungeon_Operator"), nullptr);
            if (DungeonOperator == NULL)
                return;

            Interpolate(app::Transform_get_localPosition(app::GameObject_get_transform(DungeonOperator, nullptr), nullptr), 10);
            Stage++;
        }
        else if (Stage == 2)
        {
            LOG_INFO("Hello from Stage %i", Stage);

            for (const auto &entity : game::EntityManager::instance().entities())
            {
                auto twee = FindRewardTree();
                if (twee == nullptr)
                    break;

                app::Vector3 position = twee->relativePosition();
                position.y = +2;
                Teleport(position);
                LOG_INFO("Resetting Stage");
                Stage = Stage = 1;
                f_Enabled.value().enabled = false;

                LOG_INFO("Stage Reset, back to Stage %i", Stage);
            }
        }
        StageDelay = currentTime + (int)f_Delay;
    }
}
