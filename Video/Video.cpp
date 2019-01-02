// Video.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Video.h"
#include "cv.h"
#include "highgui.h"
#include "math.h"
#include "cxcore.h"
#include <vector>

#define MAX_LOADSTRING 100
#define IDB_START	101
#define IDB_STOP	102
#define IDE_TIPS	103


int cot;//��¼���������Ƶ֡��
std::vector<POINT> vecPoint;
RECT rtResult;
HWND hEditWnd = NULL;

int xiangsupipei(char name1[50],char name2[50])
{
	int count=0;
    IplImage *img=cvLoadImage(name1,1);
    IplImage* img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    cvCvtColor(img, img_gray, CV_BGR2GRAY);
    cvThreshold(img_gray, img_gray,100, 255,CV_THRESH_BINARY);
	
	IplImage *img1=cvLoadImage(name2,1);
    IplImage* img_gray1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
    cvCvtColor(img1, img_gray1, CV_BGR2GRAY); 
    cvThreshold(img_gray1, img_gray1,100, 255,CV_THRESH_BINARY);
   
	CvScalar s,sv;
	for(int i=0;i<60;i++){
        for(int j=0;j<35;j++)
		{
        s=cvGet2D(img_gray,i,j); 
		sv=cvGet2D(img_gray1,i,j);
		if (sv.val[0]==s.val[0] ){count++;}
        }
    }
	cvReleaseImage(&img);
	cvReleaseImage(&img_gray);
	cvReleaseImage(&img1);
	cvReleaseImage(&img_gray1);
    return count;
}

/*3&9*/
int zuocexs(char name1[50])
{
   int count=0;
    IplImage *img=cvLoadImage(name1,1);
    IplImage* img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    cvCvtColor(img, img_gray, CV_BGR2GRAY);
    cvThreshold(img_gray, img_gray,100, 255,CV_THRESH_BINARY);
    CvScalar s;
	for(int i=0;i<60;i++){
        for(int j=0;j<17;j++)
		{
        s=cvGet2D(img_gray,i,j); 
		if (s.val[0]==255){count++;}
        }
    }
	cvReleaseImage(&img);
	cvReleaseImage(&img_gray);
    return count;
}

/*0&8*/
int midxiangsu(char name1[50])
{
	int count=0;
    IplImage *img=cvLoadImage(name1,1);
    IplImage* img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    cvCvtColor(img, img_gray, CV_BGR2GRAY);
    cvThreshold(img_gray, img_gray,100, 255,CV_THRESH_BINARY);	
    CvScalar s;
	for(int i=0;i<60;i++)
		{
        s=cvGet2D(img_gray,i,22); 
		if (s.val[0]==255){count++;}
        }    
	cvReleaseImage(&img);
	cvReleaseImage(&img_gray);
    return count;
}
/*����ͼ����*/
void danbu()
{
	int cott;
	char text[256];
	for(cott=1;cott<=cot;cott++)
	{
		sprintf(text, "-----------------------------------------------\r\n");
		::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
		sprintf(text, "ʶ���%d֡ͼƬ\r\n", cott);
		::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
// 		printf("-----------------------------------------------\n");
// 		printf("ʶ���%d֡ͼƬ\n",cott);
		char ytyname[30];
		sprintf(ytyname,"./yt/%d.jpg",cott);
		IplImage* src0=cvLoadImage(ytyname);
		IplImage* src=src0;
		CvScalar s;
		for(int i = 0;i < src->height;i++)
		{
			for(int j = 0;j < src->width;j++)
                {
    
                     s = cvGet2D(src,i,j); // �������ֵ
                     if(s.val[0]<60&&s.val[1]<60&&s.val[2]>140) 
    //ע�������012��Ӧ����bgr����Χ����˼�Ƿ�ֹ���ߵ�����Ӱ�죬�����ʵ��ſ�������Ҳ����ѡ����������ɫ�ռ䣬����ֱ��ȡ������Ӱ�죬����HSV
                       {
                            s.val[0]=0;
                            s.val[1]=0;
                            s.val[2]=255;
                        }  //�����������������Ϊ��ɫ
                     else
                        {
                            s.val[0]=0;
                            s.val[1]=0;
                            s.val[2]=0;
                         } //��������������Ϊ��ɫ
                     cvSet2D(src,i,j,s);   //��������
               }
       }
		cvSmooth(src,src,CV_BLUR,3,3,0,0);//ƽ������
		IplImage* img1 = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);//����Ŀ��ͼ��
		cvCvtColor(src, img1, CV_RGB2GRAY );//����Ϊ�Ҷ�ͼ
		cvThreshold(img1,img1,0,225,CV_THRESH_BINARY); //��ֵ��

	
//�Զ���1*3�ĺ˽���x��������

		IplConvKernel*kernal00=cvCreateStructuringElementEx(3,1,1,0,CV_SHAPE_RECT);
		cvDilate(img1,img1,kernal00,25);

  
		CvMemStorage *img2;
		CvSeq *pContour ;
		img2 = cvCreateMemStorage(0);
		int count0= cvFindContours(img1, img2,&pContour,sizeof(CvContour),CV_RETR_EXTERNAL); 
		sprintf(text, "����������%d\r\n", count0);
		::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
//		printf("����������%d\n",count0);
	          


/*��ȡĿ������*/	
		CvRect rect; 
		CvPoint pt1,pt2; 
		CvScalar color=CV_RGB(97,158,255);
		CvSeq* first_seq =pContour;
		for(pContour=first_seq; pContour != 0;pContour = pContour->h_next )
		{
			rect = cvBoundingRect(pContour);
			pt1.x= rect.x;pt1.y=rect.y;
			pt2.x=pt1.x+rect.width;pt2.y=pt1.y+rect.height;
			cvRectangle(img1,pt1,pt2,color,1,CV_AA,0);

		}
		IplImage *res=cvLoadImage(ytyname);

		CvMat *pMat = cvGetSubRect(res, cvCreateMatHeader(100, 100, CV_8UC1), rect);
		IplImage *dst = cvGetImage(pMat, cvCreateImageHeader(cvSize(100, 100), 8, 1));

	//Ԥ����
	IplImage* src2=dst;
    IplImage* img_hsv=cvCreateImage(cvGetSize(src2),8,3);
	IplImage* img_h=cvCreateImage(cvGetSize(src2),8,1);
	IplImage* img_s=cvCreateImage(cvGetSize(src2),8,1);
	IplImage* img_v=cvCreateImage(cvGetSize(src2),8,1);	


	cvCvtColor(src2,img_hsv,CV_BGR2HSV);
	cvSplit(img_hsv,img_h,img_s,img_v,NULL);
	cvInRangeS(img_h,cvScalar(0,0,0,0),cvScalar(200,0,0,0),img_h);  
    cvInRangeS(img_s,cvScalar(0,0,0,0),cvScalar(255,100,100,0),img_s);  
    cvInRangeS(img_v,cvScalar(175,0,0,0),cvScalar(255,0,0,0),img_v);

	IplImage *imgTemp=NULL,*imgHsvBinnary=NULL;

    imgTemp=cvCreateImage(cvGetSize(src2),src2->depth,1);
    imgHsvBinnary=cvCreateImage(cvGetSize(src2),src2->depth,1);
    cvAnd(img_h,img_s,imgTemp);
    cvAnd(imgTemp,img_v,imgHsvBinnary);


	IplConvKernel *element=0;   //�Զ����
    int values[4]={ 1,1,
		            1,1 };
    int rows=2,cols=2,anchor_x=1,anchor_y=1;
    element = cvCreateStructuringElementEx(cols,rows,anchor_x,anchor_y,CV_SHAPE_CUSTOM,values); 
		cvDilate(imgHsvBinnary,imgHsvBinnary,element,5);//�������Ͳ��� 
		cvErode(imgHsvBinnary,imgHsvBinnary,element,1); //���и�ʴ����
 cvDilate(imgHsvBinnary,imgHsvBinnary,element,2);//�������Ͳ���
 cvErode(imgHsvBinnary,imgHsvBinnary,element,1); //���и�ʴ����
	char yuchuliname[30];
    sprintf(yuchuliname,"./yuchuli/%d.jpg",cott);//����ͼ��Ԥ������ÿһ֡ͼ��
	 cvSaveImage(yuchuliname,imgHsvBinnary);


////////////////////////////////////////////////////////////////////////////////////


	/*�ָ������*/
    IplImage* imgSrc=cvLoadImage(yuchuliname,CV_LOAD_IMAGE_COLOR);;
    IplImage* img_gray = cvCreateImage(cvGetSize(imgSrc), IPL_DEPTH_8U, 1);
    cvCvtColor(imgSrc, img_gray, CV_BGR2GRAY);
    cvThreshold(img_gray, img_gray,100, 255,CV_THRESH_BINARY);
	//�Զ���˽���x����ʴ
	IplConvKernel*kernal1=cvCreateStructuringElementEx(2,1,1,0,CV_SHAPE_RECT);
	cvErode(img_gray,img_gray,kernal1,2);
	
//�Զ���3*1�ĺ˽���y��������

IplConvKernel*kernal2=cvCreateStructuringElementEx(1,3,0,1,CV_SHAPE_RECT);
	cvDilate(img_gray,img_gray,kernal2,8);


	CvSeq* contours = NULL;
    CvMemStorage* storage = cvCreateMemStorage(0);
	
    int count = cvFindContours(img_gray, storage, &contours,sizeof(CvContour),CV_RETR_EXTERNAL);
	sprintf(text, "����������%d\r\n", count);
	::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
	::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
//	printf("����������%d\n",count);	
    int idx = 0;
    char szName[30] = {0};
	double a[20]={0},b[20]={0};
	int i=0,lkpaixu[20]={0};
    for (CvSeq* c = contours; c != NULL; c = c->h_next) 
	{
        CvRect rc =cvBoundingRect(c,0);  		 
        a[i]=rc.x;b[i]=rc.x;
        IplImage* imgNo = cvCreateImage(cvSize(rc.width+2, rc.height+2), IPL_DEPTH_8U, 3); 
        cvSetImageROI(imgSrc, cvRect(rc.x-1,rc.y-1,rc.width+2,rc.height+2));
        cvCopyImage(imgSrc, imgNo);
        cvResetImageROI(imgSrc); 
        sprintf(szName, "./fgmid/%d.jpg", idx++); 
      	cvSaveImage(szName,imgNo);
    	IplImage *imageresize=0;  	//�������ַ���ͼƬ��һ����������
    	imageresize=cvCreateImage(cvSize(35,60),IPL_DEPTH_8U,3); //����һ��ͨ�óߴ� 
        cvResize(imgNo,imageresize,CV_INTER_LINEAR);  //��ͼƬ������ͨ�óߴ�
        
	
		cvSaveImage(szName,imageresize);
        cvReleaseImage(&imageresize);  
        cvReleaseImage(&imgNo); 
 
      	i++;	
	}



	/*��ȥ�����ַ�ͼƬ�����������ı���б���ָ�������ٽ��ַ���һС����*/
	for(i=0;i<count;i++)
	{
       	double minarea = 100.0;   
        double tmparea = 0.0; 
        uchar *pp;
        char nameee[56]={0};
    	sprintf(nameee,"./fgmid/%d.jpg",i);
        IplImage* imgSrc1 = cvLoadImage(nameee,CV_LOAD_IMAGE_COLOR);
        IplImage* img_gray1 = cvCreateImage(cvGetSize(imgSrc1), IPL_DEPTH_8U, 1);
        cvCvtColor(imgSrc1, img_gray1, CV_BGR2GRAY);
        cvThreshold(img_gray1, img_gray1,100, 255,CV_THRESH_BINARY);
        IplImage* img_Clone=cvCloneImage(img_gray1);
        CvSeq* conturs = NULL;
        CvMemStorage* strage = cvCreateMemStorage(0); 
        int count1 = cvFindContours(img_gray1, strage, &conturs,sizeof(CvContour),CV_RETR_EXTERNAL);
        char szName[56] = {0};
        for (CvSeq* c1 = conturs; c1 != NULL; c1 = c1->h_next)
		{
             CvRect rc1 =cvBoundingRect(c1,0);  
		     tmparea = fabs(cvContourArea(c1));  
		     if (tmparea < minarea)   
			 {    
                  pp=(uchar*)(img_Clone->imageData + img_Clone->widthStep*(rc1.y+rc1.height/2)+rc1.x+rc1.width/2);   
                  if (pp[0]==255)   
				 {   
                      for(int y = rc1.y;y<rc1.y+rc1.height;y++)   
					 {   
                           for(int x =rc1.x;x<rc1.x+rc1.width;x++)   
						  {   
                                pp=(uchar*)(img_Clone->imageData + img_Clone->widthStep*y+x);                  
                                if (pp[0]==255)   
								{   
                                    pp[0]=0;   
								}   
						   }   
					  }   
				  }  
			 }
	         
			 cvSaveImage(nameee,img_Clone);      
		} 
	//	cvNamedWindow(nameee); 
    //    cvShowImage(nameee, img_Clone);
		cvReleaseMemStorage(&strage); 
        cvReleaseImage(&imgSrc1); 
        cvReleaseImage(&img_gray1); 
    	cvReleaseImage(&img_Clone); 
	}
/*
	�Էָ�õ��ַ�ͼƬ��ԭʼ˳����
	*/
	int j,k,m;
	double l;
	for(j=0;j<count-1;j++)
		for(k=0;k<count-1-j;k++)
		{
			 if(a[k]<a[k+1])
			 {
				 l=a[k];
				 a[k]=a[k+1];
				 a[k+1]=l;
			 }
		}

     for(j=0;j<count;j++)
		 for(k=0;k<count;k++)
		 {
			  if(b[j]==a[k])
			  {
				  lkpaixu[j]=k;
			  }
		 }
		 sprintf(text, "��������˳���ɷָ���ĵ�һ��������ʼ����");
		 ::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		 ::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
	//	 printf("��������˳���ɷָ���ĵ�һ��������ʼ����");
		 for(m=0;m<count-1;m++)
		 {
			 sprintf(text, "%d", lkpaixu[m]+1);
			 ::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
			 ::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
		//	 printf("%d",lkpaixu[m]+1);
		 }
		 sprintf(text, "%d\r\n", lkpaixu[count-1]+1);
		 ::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		 ::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
		 //printf("%d\n",lkpaixu[count-1]+1);
		 cvReleaseMemStorage(&storage); 
		 cvReleaseImage(&imgHsvBinnary); 

	 //���������ַ�ƥ��ʶ��ʶ�������
		 int jieguo[20]={0};double aa[20]={0},bb[20]={0};
		 int n=0;
		 for(i=0;i<count;i++)
		 {	 
			 for(j=0;j<10;j++)
			 {
				 char src1name[30];
				 sprintf(src1name,"./mb/%d.jpg",j);
				 char src2name[30];
				 sprintf(src2name,"./fgmid/%d.jpg",i);
				 aa[j] = xiangsupipei(src1name,src2name);//�ֱ����Ŀ���ʶ���ַ���ģ���ַ�������ƥ�����
				 bb[j] = xiangsupipei(src1name,src2name);
			 }
			 char src3name[30];
			 sprintf(src3name,"./fgmid/%d.jpg",i);
			 int k,l;
			 double m;
			 for(k=0;k<9;k++)
				 for(l=0;l<9-k;l++)//ð�ݷ��Ӵ�С����aa[]
				 {
					 if(aa[l]<aa[l+1])
					 {
						 m=aa[l];
						 aa[l]=aa[l+1];
						 aa[l+1]=m;
					 }
				 }
				 for(k=0;k<10;k++)
				 {
					 if(aa[0]==bb[k])
					 {
						 jieguo[lkpaixu[n]]=k;
						 //����ʶ�����׻�����'9','3'�����ַ�
						 if(k==9)
						 {
							 if(abs(zuocexs(src3name)-zuocexs("./mb/3.jpg"))<abs(zuocexs(src3name)-zuocexs("./mb/9.jpg"))) 
							 {
								 jieguo[lkpaixu[n]]=3;
							 }
						 }
						 else if(k==3)
						 {
							 if(abs(zuocexs(src3name)-zuocexs("./mb/3.jpg"))>abs(zuocexs(src3name)-zuocexs("./mb/9.jpg"))) 
							 {
								 jieguo[lkpaixu[n]]=9;
							 }
						 }
						 //����ʶ�����׻�����'0','8'�����ַ�
                         else  if(k==8)
						 {
							 if(abs(midxiangsu(src3name)-midxiangsu("./mb/8.jpg"))>abs(midxiangsu(src3name)-midxiangsu("./mb/0.jpg"))) 
								 jieguo[lkpaixu[n]]=0;	
						 }
						 else  if(k==0)
						 {
							 if(abs(midxiangsu(src3name)-midxiangsu("./mb/8.jpg"))<abs(midxiangsu(src3name)-midxiangsu("./mb/0.jpg"))) 
								 jieguo[lkpaixu[n]]=8;	
						 }
						
						 n++;
					 }
				 }
		 }
		 int w;
		 FILE* fp=fopen("./�¶�����.txt","a");//����Ļ����ʾ�������������ļ�
		 sprintf(text, "��ǰʾ��Ϊ��");
		 ::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		 ::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
		 //printf("��ǰʾ��Ϊ��");
		 for(w=count-1;w>0;w--)
		 {
			 sprintf(text, "%d", jieguo[w]);
			 ::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
			 ::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
			 //printf("%d",jieguo[w]);
			 fprintf(fp,"%d",jieguo[w]);
		 }
		 sprintf(text, "%d\r\n", jieguo[0]);
		 ::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
		 ::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
		// printf("%d\n",jieguo[0]); 
		 fprintf(fp,"%d\n",jieguo[w]);
		 fclose(fp);
	
		 }

}



// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VIDEO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VIDEO));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIDEO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VIDEO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   rtResult.left = 80;
   rtResult.top = 50;
   rtResult.right = 650;
   rtResult.bottom = 450;

   CreateWindow("Button", "��������", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, rtResult.right+100, rtResult.bottom-80, 80, 30, hWnd, (HMENU)IDB_START, hInstance, NULL);		
   CreateWindow("Button", "�˳����", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, rtResult.right+100, rtResult.bottom-40, 80, 30, hWnd, (HMENU)IDB_STOP, hInstance, NULL);
   CreateWindow("Edit", NULL, WS_VISIBLE|WS_CHILD|ES_MULTILINE|ES_READONLY|ES_AUTOVSCROLL, rtResult.right+15, rtResult.top, 250, rtResult.bottom-rtResult.top-100, hWnd, (HMENU)IDE_TIPS, hInstance, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDB_START:
			{
				EnableWindow(GetDlgItem(hWnd,IDB_START), FALSE);
				hEditWnd = GetDlgItem(hWnd, IDE_TIPS);
				CvCapture* g_capture=cvCreateFileCapture("1.avi");//��������Ƶ�ļ�	
				IplImage* frame;
				cot=0;
				FILE* fp=fopen("./�¶�����.txt","w");fclose(fp);//����ϴ�ʶ�𱣴�������ļ�
				char text[256];
				/* ��Ƶ��֡��������ÿһ֡ */
				while(1)
				{
					frame=cvQueryFrame(g_capture);  
					if(frame)
					{
						cot++;
						sprintf(text, "��%d֡ͼƬ�ѷָ�\r\n", cot);
						::SendMessage(hEditWnd, EM_SETSEL, -1, -1);
						::SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)text);
				//		printf("��%d֡ͼƬ�ѷָ�\n",cot);
						char ytname[30];
						sprintf(ytname,"./yt/%d.jpg",cot);		
						cvSaveImage(ytname,frame);
					}
					else
					{
						cvReleaseCapture(&g_capture);
						break;
					}
				}
				cvReleaseCapture(&g_capture);//�ͷ���Ƶ��Ϣ�ṹ��
				danbu();//ִ��ͼƬԤ�����ı���λ���ָʶ���ӳ���

				vecPoint.clear();
				POINT pt;
				fp=fopen("./�¶�����.txt","r");
				pt.x = 1;
				while (!feof(fp)) 
				{ 
					fgets(text,256,fp);  //��ȡһ��
					int tmp = atoi(text);
					if (tmp>=100 && tmp<=1100)
						pt.y = atoi(text);
					vecPoint.push_back(pt);
					pt.x++;
				} 
				fclose(fp);

				InvalidateRect(hWnd, &rtResult, TRUE);
				EnableWindow(GetDlgItem(hWnd,IDB_START), TRUE);
			}
			break;
		case IDB_STOP:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// �ڴ���������ͼ����...
		{
			int scale = rtResult.bottom - rtResult.top - 20*2;
			scale /= 10;
			char p[20];
			for (int index = 0 ; index < 11 ; index++)
			{
				sprintf(p, "%d", (10-index)*100+100);
				MoveToEx(hdc, rtResult.left+40, rtResult.top+20+index*scale, NULL);
				LineTo(hdc, rtResult.right-20, rtResult.top+20+index*scale);
				TextOut(hdc, rtResult.left, rtResult.top+12+index*scale, p, strlen(p));//��������
			}
			int total_width = rtResult.right-20 - (rtResult.left+40);
			int total_height = 10*scale;
			int start_x = rtResult.left+40;
			int start_y = rtResult.bottom-20;
			scale = total_width/8;
			for (int index = 1 ; index <= 8 ; index++)
			{
				sprintf(p, "%d", index*20);
				TextOut(hdc, rtResult.left+25+index*scale, rtResult.bottom-5, p, strlen(p));//��������
			}
			sprintf(p, "�¶���Ƶ������ȡ��");
			TextOut(hdc, 440, 20, p, strlen(p));

			int count = vecPoint.size();
			HPEN gPen = CreatePen(PS_SOLID,1,RGB(0,0,255));
			HPEN oPen = (HPEN)SelectObject(hdc,gPen);
			if (count > 1)//��һ����λ��
			{
				POINT pt = vecPoint[0];
				pt.x = total_width*pt.x/160 + start_x;
				pt.y = start_y - total_height*(pt.y-100)/1000;
				MoveToEx(hdc, pt.x, pt.y, NULL);
			}
			else if (count == 1)
			{
				SetPixel(hdc,10,10,RGB(0,0,255));
			}
			for (int index = 1 ; index < count ; index++)//�������λ��
			{
				POINT pt = vecPoint[index];
				pt.x = total_width*pt.x/160 + start_x;
				pt.y = start_y - total_height*(pt.y-100)/1000;
				LineTo(hdc, pt.x, pt.y);
			}
			SelectObject(hdc, oPen);
			DeleteObject(gPen);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

