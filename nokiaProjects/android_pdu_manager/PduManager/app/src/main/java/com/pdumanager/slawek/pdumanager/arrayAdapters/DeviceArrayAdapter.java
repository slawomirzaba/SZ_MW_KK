package com.pdumanager.slawek.pdumanager.arrayAdapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.pdumanager.slawek.pdumanager.R;
import com.pdumanager.slawek.pdumanager.fragments.DevicesActivity;
import com.pdumanager.slawek.pdumanager.model.Device;

/**
 * Created by slawek on 18.08.16.
 */
public class DeviceArrayAdapter extends ArrayAdapter<Device> {
    private final LayoutInflater mInflater;
    private final int mResourceId;

    public DeviceArrayAdapter(Context context, int device_on_list) {
        super(context, device_on_list);
        mInflater = LayoutInflater.from(context);
        mResourceId = device_on_list;
    }


    public void setDevices(Device[] devices) {
        clear();
        for(Device device : devices){
            add(device);
        }
        if(isEmpty()){
            notifyDataSetInvalidated();
        } else {
            notifyDataSetChanged();
        }
    }

    public View getView(int i, View converterView, ViewGroup viewGroup){
        ViewHolder viewHolder  = null;
        if(converterView == null) {
            viewHolder = new ViewHolder();
            converterView = mInflater.inflate(mResourceId, viewGroup, false);
            viewHolder.mDeviceNameTextView = (TextView) converterView.findViewById(R.id.device_name);
            viewHolder.mDeviceDescrTextView = (TextView) converterView.findViewById(R.id.device_description);
            viewHolder.mDeviceIpTextView = (TextView) converterView.findViewById(R.id.device_ip);
            viewHolder.mDeviceContainerLinearLayout = (LinearLayout) converterView.findViewById(R.id.device_on_list);
            converterView.setTag(viewHolder);
        }else{
            viewHolder = (ViewHolder) converterView.getTag();
        }
        Device device = getItem(i);
        viewHolder.mDeviceIpTextView.setText("Ip: " + device.ip);
        viewHolder.mDeviceDescrTextView.setText("Description: " + device.descr);
        viewHolder.mDeviceNameTextView.setText("Name: " + device.name);
        viewHolder.mDeviceContainerLinearLayout.setVisibility(View.VISIBLE);
        return converterView;
    }

    private class ViewHolder {
        TextView mDeviceIpTextView;
        TextView mDeviceNameTextView;
        TextView mDeviceDescrTextView;
        LinearLayout mDeviceContainerLinearLayout;
    }
}
