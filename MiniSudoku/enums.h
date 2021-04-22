#pragma once
enum class ButtonEventType {
	None,
	Pressed,
	Released,
	Moved

};
enum class Gamestates {
	Intro,
	Main,
	Solving,
	Generating,
	Settings,
	Other,
	Debug
};
enum buttonState {
	eNone,
	eHovered,
	eClicked
};
enum other_texture_indexes {
	eBg,
	eIntroBg,
	eBgOverlay
};
enum interractable_texture_indexes {
	//TODO copy sfml name convention
	eBtn,
	eHover_btn,
	eActive_btn,

	eBox,
	eHover_box,
	eActive_box,

	eBack,
	eHover_back,
	eActive_back,

	eMedia,
	eHover_media,
	eActive_media,

	eSettings,
	eHover_settings,
	eActive_settings
};
enum class ID {
	play,
	settings,
	media,
	generate,
	solve,
	back,
	debug
};
struct MouseButtonEvent {
	ButtonEventType type;
	sf::Vector2i mousePos;
};