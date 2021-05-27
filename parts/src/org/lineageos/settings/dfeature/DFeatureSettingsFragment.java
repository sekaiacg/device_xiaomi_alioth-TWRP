/*
 * Copyright (C) 2018 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.lineageos.settings.dfeature;

import android.os.Bundle;
import android.view.MenuItem;
import android.content.Context;
import androidx.preference.Preference;
import android.content.SharedPreferences;
import androidx.preference.Preference.OnPreferenceChangeListener;
import androidx.preference.PreferenceFragment;
import androidx.preference.SwitchPreference;
import androidx.preference.ListPreference;
import android.widget.Toast;
import android.provider.Settings;
import android.os.ServiceManager;
import android.os.RemoteException;
import android.content.om.IOverlayManager;
import android.content.om.OverlayInfo;



import org.lineageos.settings.R;
import vendor.xiaomi.hardware.touchfeature.V1_0.ITouchFeature;


public class DFeatureSettingsFragment extends PreferenceFragment implements
        OnPreferenceChangeListener {
        
    private static final String KEY_MIN_REFRESH_RATE = "pref_min_refresh_rate";
    private IOverlayManager mOverlayService;
    private ListPreference mPrefMinRefreshRate;
    private SwitchPreference mPrefPillStyleNotch;
    
    
    private static final String D2TW_ENABLE_KEY = "dt2w_enable";
    public static final String SHAREDD2TW = "sharadeD2TW";
    private SwitchPreference mD2TWPreference;
    private ITouchFeature mTouchFeature;
    
     @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        getActivity().getActionBar().setDisplayHomeAsUpEnabled(true);
        mOverlayService = IOverlayManager.Stub.asInterface(ServiceManager.getService("overlay"));
    }

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
      addPreferencesFromResource(R.xml.dfeature_settings);
      mPrefMinRefreshRate = (ListPreference) findPreference(KEY_MIN_REFRESH_RATE);
      mPrefMinRefreshRate.setOnPreferenceChangeListener(this);
      
      try {
            mTouchFeature = ITouchFeature.getService();
        } catch (Exception e) {
            // Do nothing
        }
        mD2TWPreference = (SwitchPreference) findPreference(D2TW_ENABLE_KEY);
        mD2TWPreference.setEnabled(true);
        mD2TWPreference.setOnPreferenceChangeListener(this);
        enableD2TW(1);
        
    }
    
    @Override
    public void onResume() {
        super.onResume();
        updateValuesAndSummaries();
    }
    
    
     @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        final String key = preference.getKey();
        switch(key){
        
        case D2TW_ENABLE_KEY :
            enableD2TW((Boolean) newValue ? 1 : 0);
            break;
            
        case KEY_MIN_REFRESH_RATE :
             Settings.System.putFloat(getContext().getContentResolver(),
                        Settings.System.MIN_REFRESH_RATE,
                        (float) Integer.parseInt((String) newValue));
        
        }
        
        updateValuesAndSummaries();
        return true;
    }
   
        @Override
        public boolean onOptionsItemSelected(MenuItem item) {
            if (item.getItemId() == android.R.id.home) {
                getActivity().onBackPressed();
                return true;
            }
            return false;
        }
        
        //Utils Code
        private void updateValuesAndSummaries() {
        final float refreshRate = Settings.System.getFloat(getContext().getContentResolver(),
            Settings.System.MIN_REFRESH_RATE, 120.0f);
        mPrefMinRefreshRate.setValue(((int) refreshRate) + " Hz");
        mPrefMinRefreshRate.setSummary(mPrefMinRefreshRate.getValue());

        }
        
         private void enableD2TW(int enable) {
        if (mTouchFeature == null) return;
        try {
            mTouchFeature.setTouchMode(14,enable);
            SharedPreferences preferences = getActivity().getSharedPreferences(SHAREDD2TW,Context.MODE_PRIVATE);
            SharedPreferences.Editor editor = preferences.edit();
             editor.putInt(SHAREDD2TW, enable);
              editor.commit();
            }catch (Exception e) {
            // Do nothing
        }
    }
    
}
