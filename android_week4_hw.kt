package com.example.myapplication29mar2023

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import java.lang.NumberFormatException

class MainActivity : AppCompatActivity() {
    lateinit var edit1 : EditText;
    lateinit var edit2 : EditText;
    lateinit var btnAdd : Button;
    lateinit var btnSub : Button;
    lateinit var btnMul : Button;
    lateinit var btnDiv : Button;
    lateinit var btnMod : Button;
    lateinit var btnUpdate : Button;
    lateinit var textResult: TextView;

    var num1 : String? = null;
    var num2 : String? = null;
    var result: Int? = null;

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        title = "초간단 계산기"

        edit1 = findViewById<EditText>(R.id.Edit1)
        edit2 = findViewById<EditText>(R.id.Edit2)

        btnAdd = findViewById<Button>(R.id.BtnAdd)
        btnSub = findViewById<Button>(R.id.BtnSub)
        btnMul = findViewById<Button>(R.id.BtnMul)
        btnDiv = findViewById<Button>(R.id.BtnDiv)
        btnMod = findViewById<Button>(R.id.BtnMod)
        btnUpdate = findViewById<Button>(R.id.BtnUpdate)
        textResult = findViewById<TextView>(R.id.TextResult)

        btnAdd.setOnClickListener {
            num1 = edit1.text.toString()
            num2 = edit2.text.toString()

            try {
                result = Integer.parseInt(num1) + Integer.parseInt(num2)
                textResult.text = "계산 결과: " + result.toString()
            } catch (e: NumberFormatException) {
            }
            false
        }

        btnSub.setOnClickListener{
            num1 = edit1.text.toString()
            num2 = edit2.text.toString()
            try {
                result = Integer.parseInt(num1) - Integer.parseInt(num2)
                textResult.text = "계산 결과: " + result.toString()
            } catch (e: NumberFormatException) {
            }
            false
        }

        btnMul.setOnClickListener{
            num1 = edit1.text.toString()
            num2 = edit2.text.toString()
            try {
                result = Integer.parseInt(num1) * Integer.parseInt(num2)
                textResult.text = "계산 결과: " + result.toString()
            } catch (e: NumberFormatException) {
            }
            false
        }

        btnDiv.setOnClickListener{
            num1 = edit1.text.toString()
            num2 = edit2.text.toString()
            try {
                result = Integer.parseInt(num1) / Integer.parseInt(num2)
                textResult.text = "계산 결과: " + result.toString()
            } catch (e: NumberFormatException) {
            }
            false
        }

        btnMod.setOnClickListener{
            num1 = edit1.text.toString()
            num2 = edit2.text.toString()
            try {
                result = Integer.parseInt(num1) % Integer.parseInt(num2)
                textResult.text = "계산 결과: " + result.toString()
            } catch (e: NumberFormatException) {
            }
            false
        }

        btnUpdate.setOnClickListener{
//            num1 = edit1.text.toString()
//            num2 = edit2.text.toString()
//            result = Integer.parseInt(num1) % Integer.parseInt(num2)
//            textResult.text="계산 결과: " +result.toString()
            edit1.setText(result.toString())
            edit2.setText("")

            false
        }
    }
}


---------------------------------------------------
    
    <?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity"
    android:orientation="horizontal">

    <EditText
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/Edit1"
        android:hint="숫자1"
        tools:ignore="MissingConstraints" />
    <EditText
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/Edit2"
        android:hint="숫자1"
        tools:ignore="MissingConstraints" />
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/BtnAdd"
        android:text="더하기"/>
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/BtnSub"
        android:text="빼기기"/>
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/BtnMul"
        android:text="곱하기"/>
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/BtnDiv"
        android:text="나누기"
        tools:ignore="MissingConstraints" />
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/BtnMod"
        android:text="나머지"/>
    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/BtnUpdate"
        android:text="교체"/>
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_margin="10dp"
        android:id="@+id/TextResult"
        android:textSize="30dp"
        android:textColor="#FF0000"
        android:text="계산 결과: " />

</LinearLayout>
