package com.pdumanager.slawek.pdumanager.fragments;

import android.app.Fragment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListView;

import com.pdumanager.slawek.pdumanager.R;
import com.pdumanager.slawek.pdumanager.arrayAdapters.DeviceArrayAdapter;
import com.pdumanager.slawek.pdumanager.model.DeviceResponse;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class DevicesActivity extends Fragment implements AdapterView.OnItemClickListener {
    private ListView mDevicesListView;
    private DeviceArrayAdapter mDeviceArrayAdapter;
    private DeviceResponse mResponse;
    private EditText mInputSearch;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        super.onCreateView(inflater, container, savedInstanceState);
        View view = inflater.inflate(R.layout.activity_devices, container, false);
        mInputSearch = (EditText) view.findViewById(R.id.search_input);
        mDevicesListView = (ListView) view.findViewById(R.id.list_devices);
        mDeviceArrayAdapter = new DeviceArrayAdapter(this.getActivity(), R.layout.device_on_list);
        mDevicesListView.setAdapter(mDeviceArrayAdapter);
        mDevicesListView.setOnItemClickListener(this);
        try {
            JSONObject jsonObject = new JSONObject(readTextFromRawResource(R.raw.devices));
            mResponse = DeviceResponse.fromJsonObject(jsonObject);
            fillListWithDevices();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mDevicesListView.setTextFilterEnabled(true);
        mInputSearch.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                //
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                DevicesActivity.this.mDeviceArrayAdapter.getFilter().filter(charSequence.toString());
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
        return view;
    }

    private void fillListWithDevices() {
        mDeviceArrayAdapter.setDevices(mResponse.devices);
    }



    private String readTextFromRawResource(int resourceId) {

        InputStream inputStream = getResources().openRawResource(resourceId);
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();

        int i;
        try {
            i = inputStream.read();
            while (i != -1) {
                byteArrayOutputStream.write(i);
                i = inputStream.read();
            }
            inputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return byteArrayOutputStream.toString();
    }


    @Override
    public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {

    }
}
