#include <Geode/Geode.hpp>
#include <Geode/modify/Slider.hpp>

class $modify(Slider) {
	bool init(cocos2d::CCNode* target, cocos2d::SEL_MenuHandler handler, const char* bar, const char* groove, const char* thumb, const char* thumbSel, float scale) {
		if (!Slider::init(target, handler, bar, groove, thumb, thumbSel, scale)) return false;
		if (this->getID() == "position-slider") return true;

		auto failsafe = geode::WeakRef(this);
		geode::queueInMainThread([failsafe = std::move(failsafe)] {
			auto self = failsafe.lock();
			if (!self) return;

			auto* bar = self->m_sliderBar;
			bool isScaleControl = geode::cast::typeinfo_cast<GJScaleControl*>(self->getParent());

			if (isScaleControl) bar->setPositionY(2.f);
			bar->setVisible(!geode::Mod::get()->getSettingValue<bool>("opposite-day"));   
		});

		return true;
	}
};