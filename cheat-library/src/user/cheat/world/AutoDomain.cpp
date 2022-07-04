#include "pch-il2cpp.h"
#include "AutoDomain.h"

#include <helpers.h>
#include <cheat/game/EntityManager.h>
#include <cheat/events.h>


namespace cheat::feature
{
    AutoDomain::AutoDomain() : Feature(),
        NF(f_Enabled, "AUto Domain", "AutoDomain", false),
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
        ImGui::TextColored(ImColor(255, 165, 0, 255), "Balls, Does AutoDomain. Expect Bugs because fuck you lol");
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
        //bullshit
        cheat::game::EntityManager& manager = game::EntityManager::instance();
        cheat::game::Entity* avatarEntity = manager.avatar();
        app::VCBaseMove* baseMove = avatarEntity->moveComponent();
        if (baseMove == nullptr)
            return;

        app::Rigidbody* rigidBody = avatarEntity->rigidbody();
        //relative is kinda meh, desync problems
        avatarEntity->setRelativePosition(value);
    }

    static bool FindRewardTree(game::Entity* entity)
    {
        if (entity->name().find("RewardTree") != std::string::npos)
            return true;
        return false;
    }


    static void Interpolate(app::Vector3 endPos, int delay)
    {
        cheat::game::EntityManager& manager = game::EntityManager::instance();
        app::Vector3 avatarpos = manager.avatar()->absolutePosition();
        std::thread interpolate([avatarpos, endPos, &manager, delay]()
            {
                float elapsed = 0.0f;
                app::Vector3 newPos = { 0,0,0 };
                app::Vector3 speed = { 0,0,0 };

                //lambda linear interpolation
                auto lerp = [](const app::Vector3& a, const app::Vector3& b, float t) {
                    return app::Vector3{
                            a.x + (b.x - a.x) * t,
                            a.y + (b.y - a.y) * t,
                            a.z + (b.z - a.z) * t
                    };
                };
                while (elapsed <= 1.0f) {
                    newPos = lerp(avatarpos, endPos, elapsed);
                    //relative could be better?
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

            app::GameObject* DungeonOperator = app::GameObject_Find(string_to_il2cppi("/EffectPool/Eff_Gear_ElementDungeon_Operator"), nullptr);
            if (DungeonOperator == NULL)
                return;

            Interpolate(app::Transform_get_localPosition(app::GameObject_get_transform(DungeonOperator, nullptr), nullptr), 10);
            Stage++;
        }
        else if (Stage == 2)
        {
            LOG_INFO("Hello from Stage %i", Stage);

            for (const auto& entity : game::EntityManager::instance().entities())
            {
                //find Reward Tree within entity list
                if (entity->name().find("RewardTree") == std::string::npos) {
                    continue;
                }
                //to check if none found (should only happen at overworld)
                else if (entity == NULL) {
                    break;
                }
                app::Vector3 position = entity->relativePosition();
                position.y = position.y + 2;
                Teleport(position);

                LOG_INFO("Resetting Stage");

                Stage = Stage = 1;
                f_Enabled.value().enabled = false;

                LOG_INFO("Resetted Stage, now back at Stage %i", Stage);
            }
        }
        StageDelay = currentTime + (int)f_Delay;
    }
}
