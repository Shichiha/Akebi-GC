#include "pch-il2cpp.h"
#include "HideUI.h"

#include <helpers.h>
#include <cheat/events.h>

namespace cheat::feature
{
    app::GameObject* ui_camera;
    app::GameObject* DamageOverlay;
    app::GameObject* RadarOverlay;
    app::GameObject* QuestHintOverlay;
    app::GameObject* TopRightOverlay;
    app::GameObject* PingOverlay;
    app::GameObject* TeamOverlay;
    namespace SkillE {
        app::GameObject* ImageComponent;
        app::GameObject* Icon;
        app::GameObject* CD;
        app::GameObject* CDEnd;
        app::GameObject* UIEffectContainer;
        app::GameObject* ImgHighlight;
        app::GameObject* Skillpoint;
        app::GameObject* Slot2Key;
    }
    namespace SkillQ {

    }
    app::GameObject* HpOverlay;
    app::GameObject* ChatOverlay;
    app::GameObject* RewardOverlay;
    app::GameObject* InteractOverlay;
    app::GameObject* ArLevelOverlay;

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

        if (f_Enabled)
        {
            if (ui_camera == nullptr)
                ui_camera = app::GameObject_Find(string_to_il2cppi("/UICamera"), nullptr);

            if (ui_camera->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(ui_camera, false, nullptr);
        }
        else
        {
            if (ui_camera)
            {
                if (ui_camera->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(ui_camera, true, nullptr);

                ui_camera = nullptr;
            }
        }
        //dmg overlay
        if (f_DamageOverlayHide)
        {
            DamageOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ParticleDamageTextContainer"), nullptr);
            if (DamageOverlay == nullptr)
                return;

            if (DamageOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(DamageOverlay, false, nullptr);
        }
        else
        {
            if (DamageOverlay)
            {
                if (DamageOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(DamageOverlay, true, nullptr);

                DamageOverlay = nullptr;
            }
        }
        //radar overlay
        if (f_RadarOverlayHide)
        {
            RadarOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/MapInfo"), nullptr);
            if (RadarOverlay == nullptr)
                return;

            if (RadarOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(RadarOverlay, false, nullptr);
        }
        else
        {
            if (RadarOverlay)
            {
                if (RadarOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(RadarOverlay, true, nullptr);

                RadarOverlay = nullptr;
            }
        }
        //quest hint overlay
        if (f_QuestHintHide)
        {
            QuestHintOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Dialogs/DialogLayer(Clone)/InLevelQuestHintDialog/EventPanel/QuestHintTrace(Clone)/BtnTrace"), nullptr);
            if (QuestHintOverlay == nullptr)
                return;

            if (QuestHintOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(QuestHintOverlay, false, nullptr);
        }
        else
        {
            if (QuestHintOverlay)
            {
                if (QuestHintOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(QuestHintOverlay, true, nullptr);

                QuestHintOverlay = nullptr;
            }
        }
        //top btn overlay
        if (f_TopRightOverlayHide)
        {
            TopRightOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/GrpMainBtn"), nullptr);
            if (TopRightOverlay == nullptr)
                return;

            if (TopRightOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(TopRightOverlay, false, nullptr);
        }
        else
        {
            if (TopRightOverlay)
            {
                if (TopRightOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(TopRightOverlay, true, nullptr);

                TopRightOverlay = nullptr;
            }
        }
        //ping overlay
        if (f_PingOverlayHide)
        {
            PingOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/NetworkLatency"), nullptr);
            if (PingOverlay == nullptr)
                return;

            if (PingOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(PingOverlay, false, nullptr);
        }
        else
        {
            if (PingOverlay)
            {
                if (PingOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(PingOverlay, true, nullptr);

                PingOverlay = nullptr;
            }
        }
        //team overlay
        if (f_TeamOverlayHide)
        {
            TeamOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/TeamBtnContainer"), nullptr);
            if (TeamOverlay == nullptr)
                return;

            if (TeamOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(TeamOverlay, false, nullptr);
        }
        else
        {
            if (TeamOverlay)
            {
                if (TeamOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(TeamOverlay, true, nullptr);

                TeamOverlay = nullptr;
            }
        }
        //skills overlay
        if (f_SkillOverlayHide)
        {
            auto Skill2Grp = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/"), nullptr);
            if (Skill2Grp == nullptr)
                return;

            auto image = app::GameObject_GetComponentByName(Skill2Grp, string_to_il2cppi("Image"), nullptr);
            SkillE::ImageComponent = app::Component_1_get_gameObject(image, nullptr);
            SkillE::Icon = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/Icon"), nullptr);
            SkillE::CD = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/CD"), nullptr);
            SkillE::CDEnd = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/CDEnd"), nullptr);
            SkillE::UIEffectContainer = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/UIEffectContainer"), nullptr);
            SkillE::ImgHighlight = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/ImgHighlight"), nullptr);
            SkillE::Skillpoint = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2/ActionBtn_Skill2(Clone)/SkillPoint"), nullptr);
            SkillE::Slot2Key = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/ActionPanelContainer/ActionBtnPanel/GrpSkill/Skill2Grp/Slot2Key"), nullptr);

            if (SkillE::ImageComponent->fields._.m_CachedPtr != nullptr)
            {
                app::GameObject_SetActive(SkillE::ImageComponent, false, nullptr);
                app::GameObject_SetActive(SkillE::Icon, false, nullptr);
                app::GameObject_SetActive(SkillE::CD, false, nullptr);  // you only need to disable CD once for all GrpSkill
                app::GameObject_SetActive(SkillE::CDEnd, false, nullptr);
                app::GameObject_SetActive(SkillE::UIEffectContainer, false, nullptr);
                app::GameObject_SetActive(SkillE::ImgHighlight, false, nullptr);
                app::GameObject_SetActive(SkillE::Skillpoint, false, nullptr);
                app::GameObject_SetActive(SkillE::Slot2Key, false, nullptr);
            }
        }
        else
        {
            if (SkillE::ImageComponent)
            {
                if (SkillE::ImageComponent->fields._.m_CachedPtr != nullptr)
                {
                    app::GameObject_SetActive(SkillE::ImageComponent, true, nullptr);
                    app::GameObject_SetActive(SkillE::Icon, true, nullptr);
                    //app::GameObject_SetActive(SkillE::CD, true, nullptr);
                    app::GameObject_SetActive(SkillE::CDEnd, true, nullptr);
                    app::GameObject_SetActive(SkillE::UIEffectContainer, true, nullptr);
                    app::GameObject_SetActive(SkillE::ImgHighlight, true, nullptr);
                    app::GameObject_SetActive(SkillE::Skillpoint, true, nullptr);
                    app::GameObject_SetActive(SkillE::Slot2Key, true, nullptr);
                }

                SkillE::ImageComponent = nullptr;
                SkillE::Icon = nullptr;
                SkillE::CD = nullptr;
                SkillE::CDEnd = nullptr;
                SkillE::UIEffectContainer = nullptr;
                SkillE::ImgHighlight = nullptr;
                SkillE::Skillpoint = nullptr;
                SkillE::Slot2Key = nullptr;
            }
        }
        //hp bar Overlay
        if (f_HpOverlayHide)
        {
            HpOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/GameInfo"), nullptr);
            if (HpOverlay == nullptr)
                return;

            if (HpOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(HpOverlay, false, nullptr);
        }
        else
        {
            if (HpOverlay)
            {
                if (HpOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(HpOverlay, true, nullptr);

                HpOverlay = nullptr;
            }
        }
        //chat Overlay
        if (f_ChatOverlayHide)
        {
            ChatOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/Chat"), nullptr);
            if (ChatOverlay == nullptr)
                return;

            if (ChatOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(ChatOverlay, false, nullptr);
        }
        else
        {
            if (ChatOverlay)
            {
                if (ChatOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(ChatOverlay, true, nullptr);

                ChatOverlay = nullptr;
            }
        }
        //reward overlay
        if (f_RewardOverlayHide)
        {
            RewardOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/SpecialDialogs"), nullptr);
            if (RewardOverlay == nullptr)
                return;

            if (RewardOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(RewardOverlay, false, nullptr);
        }
        else
        {
            if (RewardOverlay)
            {
                if (RewardOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(RewardOverlay, true, nullptr);

                RewardOverlay = nullptr;
            }
        }
        //interact overlay
        if (f_InteractOverlayHide)
        {
            InteractOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/Pages/InLevelMainPage/GrpMainPage/InteePanel/Viewport"), nullptr);
            if (InteractOverlay == nullptr)
                return;

            if (InteractOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(InteractOverlay, false, nullptr);
        }
        else
        {
            if (InteractOverlay)
            {
                if (InteractOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(InteractOverlay, true, nullptr);

                InteractOverlay = nullptr;
            }
        }
        //ar level overlay
        if (f_ArLevelOverlayHide)
        {
            ArLevelOverlay = app::GameObject_Find(string_to_il2cppi("/Canvas/SuspendBars/PlayerExpTipsDialog"), nullptr);
            if (ArLevelOverlay == nullptr)
                return;

            if (ArLevelOverlay->fields._.m_CachedPtr != nullptr)
                app::GameObject_SetActive(ArLevelOverlay, false, nullptr);
        }
        else
        {
            if (ArLevelOverlay)
            {
                if (ArLevelOverlay->fields._.m_CachedPtr != nullptr)
                    app::GameObject_SetActive(ArLevelOverlay, true, nullptr);

                ArLevelOverlay = nullptr;
            }
        }
    }
}