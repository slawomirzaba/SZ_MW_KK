package com.pdumanager.slawek.pdumanager.model;

import java.io.Serializable;

/**
 * Created by slawek on 29.07.16.
 */
public class Device implements Serializable {
    public int id;
    public String name;
    public String ip;
    public String descr;
    public Outlet[] outlets;

    @Override
    public String toString() {
        return descr + " " + name + " " + ip + " ";
    }
}
