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
	Other
};
enum buttonState {
	eNone,
	eHovered,
	eClicked
};
enum other_texture_indexes {
	eBg,
	eIntroBg
};
enum interractable_texture_indexes {
	eBtn,
	eHover_btn,
	eActive_btn,

	eBox,
	eHover_box,
	eActive_box,

	eBack,
	eHover_back,
	eActive_back,
};
enum ID {
	ePlayID,
	eSettingsID,
	eMediaID,
	eGenerateID,
	eSolveID,
	eBackID
};
struct MouseButtonEvent {
	ButtonEventType type;
	sf::Vector2i mousePos;
};