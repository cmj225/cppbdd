#ifndef CPP_BDD_
#define CPP_BDD_

// operate with Googletest TEST_F()
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <cassert>

/**
 *  FEATURE(description)  : 테스트 대상의 기능/책임을 명시
 *  SCENARIO(description) : 테스트 목적에 대한 상황 설명
 *  GIVEN(description)    : 시나리오 진행에 필요한 값 설정
 *  WHEN(description)     : 시나리오를 진행하는데 필요한 조건 명시
 *  THEN(description)     : 시나리오를 완료했을 때, 보장해야 하는 결과를 명시
 *  AND(description)      : Can follow any of GIVEN, WHEN, THEN
 */

namespace cppbdd {

#define FEATURE(description)\
    feature(description);

#define SCENARIO(description)\
    scenario(description);

#define GIVEN(description)\
    given(description);

#define WHEN(description)\
    when(description);

#define THEN(description)\
    then(description);

#define AND(description)\
    et(description);

class BDDUtil {
public:
  BDDUtil() : m_Feature(false), m_Scenario(false), m_Given(false),
              m_When(false), m_Then(false) {};
  virtual ~BDDUtil() {};

  void feature(const std::string &description) {
    if (isEnd()) {
      reset();
    }
    else {
      if (m_Feature) {
        printMessage("ERROR   ", "previous test isn't ended");
        assert(false);
      }
    }
    m_Feature = true;
    printMessage("FEATURE   ", description);
  };

  void scenario(const std::string &description) {
    if (isEnd()) {
      reset();
    }
    else {
      if (!m_Feature) {
        printMessage("ERROR   ", "FEATURE clause missing.");
        assert(false);
      }
    }
    m_Feature = m_Scenario = true;
    printMessage("SCENARIO   ", description);
  };

  void given(const std::string &description) {
    if (isEnd()) {
      reset();
    }
    else {
      if (!m_Scenario) {
        printMessage("Error   ", "SCENARIO clause missing.");
        assert(false);
      }
    }
    m_Feature = m_Scenario = m_Given = true;
    printMessage("GIVEN   ", description);
  };

  void when(const std::string &description) {
    if (isEnd()) {
      reset();
    }
    else {
      if (!m_Scenario) {
        printMessage("Error", "GIVEN clause missing.");
        assert(false);
      }
    }
    m_Feature = m_Scenario = m_Given = m_When = true;
    printMessage("When   ", description);
  };

  void then(const std::string &description) {
    if (isEnd()) {
      reset();
    }
    else {
      if (!m_When) {
        printMessage("Error   ", "WHEN clause missing.");
        assert(false);
      }
    }
    m_Feature = m_Scenario = m_Given = m_When = m_Then = true;
    printMessage("Then   ", description);
  };

  // and
  void et(const std::string &description) {
    if (m_Given || m_When || m_Then) {
      printMessage("And   ", description);
    } else {
      printMessage("ERROR   ", "AND must follow one of GIVEN, WHEN or THEN.");
      assert(false);
    }
  };

private:
  // check test end
  bool isEnd() {
    if (m_Feature && m_Scenario && m_Given && m_When && m_Then)
      return true;

    return false;
  }

  void reset() {
    m_Feature  = false;
    m_Scenario = false;
    m_Given    = false;
    m_When     = false;
    m_Then     = false;
  }

  // printing util
  void printMessage(const std::string &type, const std::string &message) {
    std::cout << std::right << std::setw(16) << type << message << std::endl;
  }

private:
  bool m_Feature  = false;
  bool m_Scenario = false;
  bool m_Given    = false;
  bool m_When     = false;
  bool m_Then     = false;
};

} // cppbdd
#endif