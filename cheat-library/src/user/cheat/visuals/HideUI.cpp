#include "pch-il2cpp.h"
#include "HideUI.h"

#include <helpers.h>
#include <cheat/events.h>

namespace cheat::feature
{
    HideUI::HideUI() : Feature(),
        NFEX(f_Enabled, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_DamageOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_RadarOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_QuestHintHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_TopRightOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_PingOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_TeamOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_SkillOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_HpOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_ChatOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),

        NFEX(f_RewardOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_InteractOverlayHide, "Hide UI", "HideUI", "Visuals", false, false),
        NFEX(f_ArLevelOverlayHide, "Hide UI", "HideUI", "Visuals", false, false)
    {
        events::GameUpdateEvent += MY_METHOD_HANDLER(HideUI::OnGameUpdate);
    }

    const FeatureGUIInfo& HideUI::GetGUIInfo() const
    {
        static const FeatureGUIInfo info{ "HideUI", "Visuals", false };
        return info;
    }

    void HideUI::DrawMain()
    {
        ConfigWidget(f_Enabled, "Hide in-game UI.\nWhen you switch to another scene (e.g. into Domains), turn off and re-enable this feature");
        ImGui::BeginGroupPanel("Advance Hide UI");
        {
            ImGui::Text("Please get into the game before using any function below!");
            ConfigWidget("Hide Damage Overlay", f_DamageOverlayHide, "Hide/Unhide damage output overlay");
            ConfigWidget("Hide Radar Overlay", f_RadarOverlayHide, "Hide/Unhide radar and top left buttons overlay");
            ConfigWidget("Hide Quest Hint Overlay", f_QuestHintHide, "Hide/Unhide quest hint overlay");
            ConfigWidget("Hide Top Buttons Overlay", f_TopRightOverlayHide, "Hide/Unhide top right buttons overlay");
            ConfigWidget("Hide Ping Overlay", f_PingOverlayHide, "Hide/Unhide ping overlay");
            ConfigWidget("Hide Team Overlay", f_TeamOverlayHide, "Hide/Unhide team overlay");
            ConfigWidget("Hide Skills Overlay", f_SkillOverlayHide, "Hide/Unhide bottom right elemental skill and ultimate overlay");
            ConfigWidget("Hide HP & EXP Bar Overlay", f_HpOverlayHide, "Hide/Unhide HP bar and EXP overlay");
            ConfigWidget("Hide Chat Overlay", f_ChatOverlayHide, "Hide/Unhide chat box overlay");
            ConfigWidget("Hide Interact Overlay", f_InteractOverlayHide, "Hide/Unhide interact overlay (press F to...)");
            ConfigWidget("Hide Rewards Overlay", f_RewardOverlayHide, "Hide/Unhide rewards overlay");
            ConfigWidget("Hide AR Level Notification Overlay", f_ArLevelOverlayHide, "Hide/Unhide AR level notification overlay");
        }
        ImGui::EndGroupPanel();
    }

    bool HideUI::NeedStatusDraw() const
    {
        return f_Enabled;
    }

    void HideUI::DrawStatus()
    {
        ImGui::Text("HideUI");
    }

    HideUI& HideUI::GetInstance()
    {
        static HideUI instance;
        return instance;
    }

    void HideUI::OnGameUpdate()
    {
        UPDATE_DELAY(500);

        std::map<bool, app::GameObject*> paths = {
            {f_Enabled,app::GameObject_Find(string_to_il2cppi("/UICamera"), nullptr)},
            {f_DamageOverlayHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ParticleDamageTextContainer"), nullptr)},
            {f_RadarOverlayHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/MapInfo"), nullptr)},
            {f_QuestHintHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Dialogs/DialogLayer(Clone)/InLevelQuestHintDialog/EventPanel/QuestHintTrace(Clone)/BtnTrace"), nullptr)},
            {f_TopRightOverlayHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/GrpMainBtn"), nullptr)},
            {f_PingOverlayHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/NetworkLatency"), nullptr)},
            {f_TeamOverlayHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/TeamBtnContainer"), nullptr)},
            {f_HpOverlayHide,app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/GameInfo"), nullptr)},
            {f_ChatOverlayHide,app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/Chat"), nullptr)},
            {f_RewardOverlayHide,app::GameObject_Find(string_to_il2cppi("/Canvas/SpecialDialogs"), nullptr)},
            {f_InteractOverlayHide, app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/InteePanel/Viewport"), nullptr)},
            {f_ArLevelOverlayHide,app::GameObject_Find(string_to_il2cppi("/Canvas/SuspendBars/PlayerExpTipsDialog"), nullptr)}
        };

        for (auto &path : paths)
        {
            bool exists = path.second->fields._.m_CachedPtr != nullptr;
            if (exists)
                app::GameObject_SetActive(path.second, !(path.first && path.second!=nullptr), nullptr);
        }

        if (f_SkillOverlayHide)
        {

            auto Skill2Grp = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/"), nullptr);
            if (Skill2Grp == nullptr)
                return;
            auto Skill5Grp = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/"), nullptr);
            if (Skill5Grp == nullptr)
                return;
            auto imageSkill2 = app::GameObject_GetComponentByName(Skill2Grp, string_to_il2cppi("Image"), nullptr);
            auto imageSkill5 = app::GameObject_GetComponentByName(Skill5Grp, string_to_il2cppi("Image"), nullptr);
            auto skillRoot = "/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel";
            std::map<std::string, std::vector<app::GameObject *>> SkillOverlays{
                {"SkillE",
                 {app::Component_1_get_gameObject(imageSkill2, nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/Icon",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/CD",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/CDEnd",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/UIEffectContainer",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/ImgHighlight",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/SkillPoint",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/GrpSkill/Skill2Grp/Slot2Key",skillRoot)), nullptr)}},

                {"SkillQ",
                 {app::Component_1_get_gameObject(imageSkill5, nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/MaxHalo",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/Effect",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/Icon",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/Progress",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/EnergyEffect",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/CD",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/CDEnd",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5/ActionBtn_Skill5_PC(Clone)/UIEffectContainer",skillRoot)), nullptr),
                  app::GameObject_Find(string_to_il2cppi(fmt::format("{}/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/Skill5Grp/Slot5Key",skillRoot)), nullptr)}}};
            for (auto &skill : SkillOverlays)
                for (auto &obj : skill.second)
                    if (obj->fields._.m_CachedPtr != nullptr)
                        app::GameObject_SetActive(obj, f_SkillOverlayHide, nullptr);    
        }
        
        
    }
}