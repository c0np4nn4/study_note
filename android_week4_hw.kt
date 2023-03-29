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
