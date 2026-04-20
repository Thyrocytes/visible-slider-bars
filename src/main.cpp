#include <Geode/Geode.hpp>
#include <Geode/modify/Slider.hpp>

struct VisibleBarSlider final : public geode::Modify<VisibleBarSlider, Slider> {
	bool init(cocos2d::CCNode* target, cocos2d::SEL_MenuHandler handler, char const* bar, char const* groove, char const* thumb, char const* thumbSel, float scale) noexcept {
		if (!Slider::init(target, handler, bar, groove, thumb, thumbSel, scale)) return false;

		this->runAction(geode::cocos::CallFuncExt::create([this]() noexcept {
			if (this->getID() == "position-slider") return;
			this->updateBar();

			bool isScaleControl = geode::cast::typeinfo_cast<GJScaleControl*>(this->getParent());

			if (isScaleControl) m_sliderBar->setPositionY(2.f);
			m_sliderBar->setVisible(!geode::Mod::get()->getSettingValue<bool>("opposite-day"));
		}));

		return true;
	}
};