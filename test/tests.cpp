// Copyright (c) 2018 Jidesh Veeramachaneni
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).

#include "gtest/gtest.h"
#include "LoopWaiter.h"
#include "fff.h"

extern "C" {
  unsigned long mock_millis ();
}

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(unsigned long, mock_millis);

class UnitTests : public ::testing::Test {
protected:
  UnitTests() {}
  virtual ~UnitTests() {}
  
  void SetUp() override {
    RESET_FAKE(mock_millis);
    m_lw = std::unique_ptr<LoopWaiter<unsigned long>>(new LoopWaiter<unsigned long>(mock_millis));
  }
  
  void TearDown() override {
    m_lw = nullptr;
  }
  
  std::unique_ptr<LoopWaiter<unsigned long>> m_lw;
};

TEST_F (UnitTests, construct_destruct) {
  ASSERT_EQ(mock_millis_fake.call_count, 0);
}

TEST_F (UnitTests, 10_seconds_repeat_exact) {
  mock_millis_fake.return_val = 1314;
  m_lw->Start(10000);
  mock_millis_fake.return_val = 11314;
  EXPECT_EQ(true, m_lw->Expired());
  EXPECT_EQ(false, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 4);
}

TEST_F (UnitTests, 10_seconds_repeat_over) {
  mock_millis_fake.return_val = 1314;
  m_lw->Start(10000);
  mock_millis_fake.return_val = 21314;
  EXPECT_EQ(true, m_lw->Expired());
  EXPECT_EQ(false, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 4);
}

TEST_F (UnitTests, 10_seconds_repeat_twice) {
  mock_millis_fake.return_val = 1314;
  m_lw->Start(10000);
  mock_millis_fake.return_val = 11314;
  EXPECT_EQ(true, m_lw->Expired());
  mock_millis_fake.return_val = 21314;
  EXPECT_EQ(true, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 5);
}

TEST_F (UnitTests, not_started) {
  EXPECT_EQ(false, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 0);
}

TEST_F (UnitTests, 10_seconds_repeat_stopped) {
  mock_millis_fake.return_val = 1314;
  m_lw->Start(10000);
  mock_millis_fake.return_val = 11314;
  EXPECT_EQ(true, m_lw->Expired());
  m_lw->Stop();
  mock_millis_fake.return_val = 21314;
  EXPECT_EQ(false, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 3);
}

TEST_F (UnitTests, 10_seconds_repeat_overflow) {
  mock_millis_fake.return_val = std::numeric_limits<unsigned long>::max() - 1;
  m_lw->Start(10000);
  mock_millis_fake.return_val = 9999;
  EXPECT_LT(9999, std::numeric_limits<unsigned long>::max());
  EXPECT_EQ(true, m_lw->Expired());
  mock_millis_fake.return_val = 19999;
  EXPECT_EQ(true, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 5);
}

TEST_F (UnitTests, 10_seconds_not_expired) {
  mock_millis_fake.return_val = std::numeric_limits<unsigned long>::max() - 1;
  m_lw->Start(10000);
  mock_millis_fake.return_val = 9998;
  EXPECT_EQ(false, m_lw->Expired());
  mock_millis_fake.return_val = 10000;
  EXPECT_EQ(true, m_lw->Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 4);
}

TEST_F (UnitTests, 10_seconds_no_repeat) {
  LoopWaiter<unsigned long> lw(mock_millis,false);
  mock_millis_fake.return_val = std::numeric_limits<unsigned long>::max() - 1;
  lw.Start(10000);
  mock_millis_fake.return_val = 9999;
  EXPECT_EQ(true, lw.Expired());
  mock_millis_fake.return_val = 19999;
  EXPECT_EQ(false, lw.Expired());
  ASSERT_EQ(mock_millis_fake.call_count, 2);
}
