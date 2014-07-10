#ifndef Preload_h__
#define Preload_h__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class PreloadLayer: public Layer {
public:
	static cocos2d::Scene* createScene();
	void PreloadAllMedias();

	virtual bool init() override;

	CREATE_FUNC(PreloadLayer)
private:

	void ASyncImageCallback(Texture2D* t2d);
	int _totalImages, _loadedImages;

	LoadingBar *loadingBar;
	TextBMFont *loadingText;

};


#endif // Preload_h__
