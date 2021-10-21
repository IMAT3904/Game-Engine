#include "EventTests.h"

TEST(Events, ResizeConstructor) {
	Engine::WindowResizeEvent e(800, 600);

	int32_t width1 = e.getwidth();
	int32_t height1 = e.getheight();

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
	EXPECT_EQ(cat, Engine::EventCategoryWindow);
	EXPECT_TRUE(e.isincategory(Engine::EventCategoryWindow));
	EXPECT_EQ(type, statictype);
	EXPECT_EQ(type, Engine::EventType::WindowResize);
	EXPECT_TRUE(false);
}