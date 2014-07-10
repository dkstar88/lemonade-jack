#include "Preload.h"
#include "SoundUtil.h"
#include "ValueMapMacros.h"
#include "MenuScene.h"


void PreloadLayer::PreloadAllMedias()
{

	ValueMap preload_map = FileUtils::getInstance()->getValueMapFromFile("preload.plist");
	ValueVector preload_images = preload_map["images"].asValueVector();
	this->_totalImages = preload_images.size();
	this->_loadedImages = 0;
	for (auto image : preload_images) {
		TextureCache::getInstance()->addImageAsync(image.asString(), CC_CALLBACK_1(PreloadLayer::ASyncImageCallback, this));
	}

}

bool PreloadLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	ADD_JSON_WIDGET("studio/preload.ExportJson");
	loadingBar = SEEK_WIDGET(LoadingBar*, widget, "loading_progress");
	loadingBar->setPercent(0);
	loadingText = SEEK_WIDGET(TextBMFont*, widget, "loading_label");
	loadingText->setString("Loading ...");
	PreloadAllMedias();
	return true;
}

cocos2d::Scene* PreloadLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PreloadLayer::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void PreloadLayer::ASyncImageCallback(Texture2D* t2d)
{
	_loadedImages++;
	if (loadingBar)
		loadingBar->setPercent((float)_loadedImages / _totalImages * 100);
	if (_loadedImages >= _totalImages) {
		SoundUtil::preloadSounds("sfx.plist");
		Director::getInstance()->replaceScene(MenuScene::createScene());
	}
}