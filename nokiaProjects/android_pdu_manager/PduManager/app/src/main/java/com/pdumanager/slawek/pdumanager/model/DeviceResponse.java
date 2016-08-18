package com.pdumanager.slawek.pdumanager.model;

import com.google.gson.Gson;

import org.json.JSONObject;

import java.io.Serializable;

/**
 * Created by slawek on 29.07.16.
 */
public class DeviceResponse implements Serializable {
    public Device[] devices;

    public static DeviceResponse fromJsonObject(JSONObject jsonObject){
        Gson gson = new Gson();
        return gson.fromJson(jsonObject.toString(), DeviceResponse.class);
    }
}
