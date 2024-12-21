/** \file LSS_t.cc 
 * Test definitions for the lss basic tests.
 *
 * (c) Copyright by MindPerfect Technologies
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include "Expect.hh"
// Std includes
// Google Test
#include <gtest/gtest.h>
#include <absl/log/log.h>

using namespace std;
using namespace MP;



TEST(Expect, Base)
{
	
	
	Expect([]() { return true; }, Error_code::logic_error);
	ASSERT_TRUE(true); // No throwing since expected value is true
	
	Expect<Error_action::ignore>([]() { return false; }, Error_code::logic_error);
	ASSERT_TRUE(true); // No throwing since ignore is specfified
	
	int i=1;
	Expect([=] { return i>0; }, Error_code::range_error);
	ASSERT_TRUE(true);
	
	// this tests _that_ the expected exception is thrown
    EXPECT_THROW({
        try
        {
			Expect<Error_action::throwing>([]() { return false; }, Error_code::logic_error);
        }
        catch( const Error_code& e )
        {
            // and this tests that it has the correct message
            EXPECT_TRUE( e == Error_code::logic_error );
            throw;
        }
    }, Error_code );
	
	EXPECT_EXIT({Expect<Error_action::terminating>([]() { return false; }, Error_code::logic_error);},
		//testing::ExitedWithCode(0), "Success");
		testing::KilledBySignal(6), ".*");
	
	//LOG(INFO) << "Custom message: Checking if value is locked.";
}
