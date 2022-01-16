#include "EventTests.h"

//Function Tests
TEST(Events, ResizeContructor) {
	Engine::WindowResizeEvent e(800, 600);
	int32_t width1 = e.getsize().x;
	int32_t height1 = e.getsize().y;

	auto size = e.getsize();
	int32_t width2 = size.x;
	int32_t height2 = size.y;

	int32_t cat = e.getcategoryflags();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();

	EXPECT_EQ(width1, 800);
	EXPECT_EQ(width2, 800);
	EXPECT_EQ(height1, 600);
	EXPECT_EQ(height2, 600);
	EXPECT_EQ(cat,Engine::EventCategoryWindow);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
}

TEST(Events, MovedConstructor) {
	Engine::WindowMovedEvent e(300, 900);
	int32_t width1 = e.getpos().x;
	int32_t height1 = e.getpos().y;

	auto size = e.getpos();
	int32_t width2 = size.x;
	int32_t height2 = size.y;

	int32_t cat = e.getcategoryflags();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();

	EXPECT_EQ(width1, 300);
	EXPECT_EQ(width2, 300);
	EXPECT_EQ(height1, 900);
	EXPECT_EQ(height2, 900);
	EXPECT_EQ(cat, Engine::EventCategoryWindow);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryWindow));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::WindowMoved);
}

TEST(Events, KeyCodeConstructor) {
	Engine::KeyPressed e(32);
	int32_t cat = e.getcategoryflags();
	int keycode = e.getkeycode();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();
	EXPECT_EQ(keycode, NG_KEY_SPACE);
	EXPECT_EQ(cat, Engine::EventCategoryKeyboard);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryKeyboard));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::KeyPressed);
}

TEST(Events, KeyCodeReleasedConstructor) {
	Engine::KeyReleased e(258);
	int32_t cat = e.getcategoryflags();
	int keycode = e.getkeycode();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();
	EXPECT_EQ(keycode, NG_KEY_TAB);
	EXPECT_EQ(cat, Engine::EventCategoryKeyboard);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryKeyboard));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::KeyReleased);
}

TEST(Events, MouseButtonConstructor) {
	Engine::MouseButtonPressedEvent e(0);
	int32_t cat = e.getcategoryflags();
	int button = e.getbutton();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();
	EXPECT_EQ(button, NG_MOUSE_BUTTON_1);
	EXPECT_EQ(cat, Engine::EventCategoryMouse);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::MouseButtonPressed);
}

TEST(Events, MouseButtonReleasedConstructor) {
	Engine::MouseButtonReleasedEvent e(1);
	int32_t cat = e.getcategoryflags();
	int button = e.getbutton();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();
	EXPECT_EQ(button, NG_MOUSE_BUTTON_2);
	EXPECT_EQ(cat, Engine::EventCategoryMouse);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::MouseButtonReleased);
}

TEST(Events, MouseMovedConstructor) {
	Engine::MouseMovedEvent e(100,100);
	int32_t cat = e.getcategoryflags();
	glm::vec2 pos = e.getpos();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();
	EXPECT_EQ(pos.x, 100);
	EXPECT_EQ(pos.y, 100);
	EXPECT_EQ(pos.x, pos.y);
	EXPECT_EQ(cat, Engine::EventCategoryMouse);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::MouseMoved);
}

TEST(Events, MouseScrolledContructor) {
	Engine::MouseScrolledEvent e(0,5);
	int32_t cat = e.getcategoryflags();
	uint32_t yoffset = e.getyoffset();
	Engine::EventType type = e.gettype();
	Engine::EventType statictype = e.getstatictype();
	EXPECT_EQ(yoffset, 5);
	EXPECT_EQ(cat, Engine::EventCategoryMouse);
	EXPECT_TRUE(e.isincategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::MouseScrolled);
}