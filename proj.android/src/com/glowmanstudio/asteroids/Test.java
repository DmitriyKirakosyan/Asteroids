/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.glowmanstudio.asteroids;

import android.app.ProgressDialog;
import android.content.Context;
import android.util.Log;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;

public class Test extends GPGSActivity{

	static Context mContext;
	
	// tag for debug logging
	final boolean ENABLE_DEBUG = true;

	// request codes we use when invoking an external activity
	public final int RC_RESOLVE = 5000, RC_UNUSED = 5001;
	final String TAG = "Asteroids ProBigi";
	
    protected void onCreate(Bundle savedInstanceState){
    	enableDebugLog(ENABLE_DEBUG, TAG);
		super.onCreate(savedInstanceState);
		mContext = Test.this;
		//super.beginUserInitiatedSignIn();
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Test should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

	@Override
	public void onSignInFailed() {
		Log.e("Google Play onSignInFailed", "Oh NOOO! ");
	}

	@Override
	public void onSignInSucceeded() {
		Log.i("Google Play onSignInSucceeded", "FUCK YEAH!");
	}



	static {
        System.loadLibrary("cocos2dcpp");
    }

	public static void gameServicesSignIn() {
		((Test)mContext).runOnUiThread(new Runnable() {
			public void run() {
				((Test) mContext).beginUserInitiatedSignIn();
			}
		});

	}

	public static void updateTopScoreLeaderboard(int score) {
		((Test)mContext).getGamesClient().submitScore("leaderboardid",
				score);
	}

	public static void updateAchievement(String id, int percentage) {

		((Test)mContext).getGamesClient().incrementAchievement(id,percentage);
	}

	public static void showLeaderboards() {
		Log.i("hz", "show leaderboard");
		((Test)mContext).runOnUiThread(new Runnable() {
			public void run() {
				((Test)mContext).startActivityForResult(((Test)mContext).getGamesClient().getLeaderboardIntent("leaderboardidfromgoogleplay"), 5001);
			}
		});
	}

	public static void showAchievements() {
		((Test)mContext).runOnUiThread(new Runnable() {
			public void run() {
				((Test)mContext).startActivityForResult(((Test)mContext).getGamesClient().getAchievementsIntent(), 5001);
			}
		});
	}


}

