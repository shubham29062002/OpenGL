#include"test.h"
#include"imgui/imgui.h"

namespace test {
	test::TestMenu::TestMenu(Test*& currentTestPointer)
		:m_Current_test(currentTestPointer)
	{

	}

	void test::TestMenu::OnImGui()
	{
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str()))
				m_Current_test = test.second();
		}
	}	
}