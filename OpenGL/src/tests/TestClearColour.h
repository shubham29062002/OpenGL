#pragma once

#include "test.h"

namespace test {
	class TestClearColour : public Test 
	{
	public:
		TestClearColour();
		~TestClearColour();

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImGui() override;
	private:
		float m_ClearColour[4];
	};
}