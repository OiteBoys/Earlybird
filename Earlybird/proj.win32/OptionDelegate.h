#pragma once
class OptionDelegate
{
public:
	OptionDelegate(void);
	virtual ~OptionDelegate(void);
	virtual void onGameStart(void);
	virtual void onGamePlaying(void);
	virtual void onGameEnd(void);
};

