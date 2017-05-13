﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;
using System.Windows.Forms;

//DirectShowLib;
using DirectShowLib;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

//ffmpeg
using AForge;
using Accord.Video.FFMPEG;

namespace RapidCheck
{
    public partial class Form1
    {
        
        public void FFMPEG_TEST()
        {
            // create instance of video reader
            Accord.Video.FFMPEG.VideoFileReader reader = new Accord.Video.FFMPEG.VideoFileReader();
            // open video file
            //reader.Open(@"C:\Users\trevor\Desktop\Videos\cctv2.wmv"); //local path
            reader.Open(@"C:\videos\tracking.mp4"); //public pc path
            Bitmap[] objBitmap = new Bitmap[nrow];

            string fmt = "0000";
            // read video frames out of it
            int j = 0;//3078, 6950, 10686, 11066==31000Frame
            for (int i = 0; i < 10000/*reader.FrameCount*/; i++) //i = frameNum
            {
                //make...folder... 일단 폴더에 저장해보자 //SQL에서 DISTINCT해서 불러와도 무관..속돈 나중에
                Bitmap videoFrame = reader.ReadVideoFrame();
                //if (i < 30000) { videoFrame.Dispose(); continue; }
                for (; i == trackingData[j].frameNum; j++) // j == row number
                {
                    makeFolder(@"C:\videos\obj\" + trackingData[j].objId);
                    //corp
                    //objBitmap[j] = cropImage(videoFrame, new Rectangle(trackingData[j].x, trackingData[j].y, trackingData[j].w, trackingData[j].h));
                    //objBitmap[j].Save(@"C:\videos\obj\" + trackingData[j].objId + "\\" + j + ".bmp");
                    
                    //string filePath = @"C:\videos\obj\" + trackingData[j].objId + @"\" + j + ".bmp";
                    string filePath = @"C:\videos\obj\" + trackingData[j].objId + @"\" + j.ToString(fmt) +".bmp";
                    System.IO.FileInfo fi = new System.IO.FileInfo(filePath);
                    if(!fi.Exists)//파일이 없으면
                    {
                        cropImage(videoFrame, new Rectangle(trackingData[j].x, trackingData[j].y, trackingData[j].w, trackingData[j].h)).Save(filePath);
                    }
                }
                // dispose the frame when it is no longer required
                videoFrame.Dispose();
            }
            //MessageBox.Show(j.ToString());
            reader.Close();
        }
        private static Bitmap cropImage(Bitmap img, Rectangle cropArea)
        {
            return img.Clone(cropArea, img.PixelFormat);
        }
        private static void makeFolder(string filePath)
        {
            System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(filePath);//Create Directoryinfo value by sDirPath  
            if (di.Exists == false)//If New Folder not exits  
            {  
                di.Create();//create Folder  
            }  
        }
    }
}
