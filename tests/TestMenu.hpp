
#include "Test.hpp"

namespace test
{

class TestMenu : public Test
{
private:
    Test* test = nullptr;
public:
    ~TestMenu();

    void OnGuiRender() override;
    void OnRender(const Renderer& renderer) override;
};

}