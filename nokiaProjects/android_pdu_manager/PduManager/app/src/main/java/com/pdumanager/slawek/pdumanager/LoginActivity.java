package com.pdumanager.slawek.pdumanager;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class LoginActivity extends AppCompatActivity implements View.OnClickListener {
    private Button mLoginButton;
    private EditText mUsernameEditText;
    private EditText mPasswordEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        mLoginButton = (Button) findViewById(R.id.button_login);
        mUsernameEditText = (EditText) findViewById(R.id.username_input);
        mPasswordEditText = (EditText) findViewById(R.id.password_input);

        mLoginButton.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        String username = mUsernameEditText.getText().toString();
        String password = mPasswordEditText.getText().toString();

        Intent intent = new Intent(this, MenuActivity.class);
        startActivity(intent);
    }
}
