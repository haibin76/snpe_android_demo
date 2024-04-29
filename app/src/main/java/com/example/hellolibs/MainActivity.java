package com.example.hellolibs;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import com.example.hellolibs.AssetCopyer;
/*
 * Simple Java UI to trigger jni function. It is exactly same as Java code
 * in hello-jni.
 */
public class MainActivity extends AppCompatActivity {

    //对调用的Native Jni函数的一些参数做声明
    private static final String dlcFile_ = "9_best_quantized_512.dlc";
    private static final String runTime_ = "dsp"; //"cpu" "gpu" "dsp"
    private static final String dataFmt_ = "USERBUFFER_FLOAT"; //only support
    private static final boolean useOpengl_ = false;

    private static final int    inWidth_ = 1280;
    private static final int    inHeight_ = 800;
    private static final int    inChannel_ = 1;
    private static final int    outWidth_ = 512;
    private static final int    outHeight_ = 512;
    private static final int    outChannel_ = 1;

    //Native JNI的函数，对ADSP_LIBRARY_PATH和LD_LIBRARY_PATH进行设置
    public native boolean setAdspLibraryPath(String j_dsp_env);

    //Native JNI的函数，在整个工程初始化的时候，被调用，整个函数的参数，在JNI层有详细的注释
    public native int  initJni(
                                   String dlc_file,String run_time,String data_fmt,boolean use_opengl,
                                   int j_in_width, int j_in_height, int j_in_channel,
                                   int j_out_width, int j_out_height, int j_out_channel);

    //Native JNI的函数，每一帧读取的Y，传递到JNI层，同时要做推理，目前还未实现
    public native int  referenceJni(byte[] img_y);

    //Native JNI的函数，工程退出的时候，调用该函数释放掉
    public native int uninitJni();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        TextView tv = new TextView(this);
        tv.setText( "The calculation took " + " ticks" );
        setContentView(tv);

        //#0 设置SNPE DSP的环境变量
        String path = getApplication().getApplicationInfo().nativeLibraryDir;
        setAdspLibraryPath(path);

        //#1再调用初始化的函数，来初始化SnpeSDK
        initJNISnpeEngine();

        try {
            referenceJNISnpeEngine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public native long  uninit();
    static {
        System.loadLibrary("hello-libs");
    }

    public void referenceJNISnpeEngine() throws IOException, InterruptedException {
        Log.d("Action", "onDetectButtonClick start");

        // 获取模型文件路径并创建文件对象
        // 从assets资源中读取图像数据
        AssetManager assetManager = getAssets(); // 获取AssetManager实例
        String[] files = assetManager.list("1280x800");
        for(int i = 0; i< files.length; i++){
            Log.d("Action_i", files[i]);
            InputStream is = assetManager.open("1280x800/"+files[i]); // 从assets子文件夹中读取图片
            int length = is.available();
            Log.d("Action", files[i] + "readFileFromAssets length:" + length);
            byte[] buffer = new byte[length];
            is.read(buffer);
            is.close();

            referenceJni(buffer);
        }
    }

    public void initJNISnpeEngine()
    {
        //#0 检查有没有模型文件，如果没有模型文件就报错，有模型文件就将模型文件COPY到SDCARD上，
        //这也是无奈之举，JNI层只需要dlc的文件路径和文件名字，而ASSETS的文件夹中文件，不能为JNI层访问
        String srcPath = "dlc";
        String dstPath = this.getExternalFilesDir(null).getAbsolutePath();
        AssetCopyer.copyAllAssets(this.getApplicationContext(),srcPath,dstPath);

        //#1通过JNI层的init函数，初始化JNISnpeEngine
        String dlcFile = dstPath + "/" + dlcFile_;
        int iRet = initJni(
                dlcFile, runTime_, dataFmt_, useOpengl_,
                inWidth_,inHeight_,inChannel_,
                outWidth_, outHeight_, outChannel_);
        if (iRet < 0) {
            Log.d("Action", "initJni failed!");
            return;
        }
        return;
    }
}
