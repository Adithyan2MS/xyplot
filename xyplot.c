#include "pbPlots.c"
#include "supportLib.c"
#include <stdio.h>
#include<stdlib.h>
int point=0;
struct plot
{
    double x;
    double y;
};
int group(struct plot peak[100],int len,struct plot axis[len])
{
    int flag=0;
    int k=0;
    for(int i=0;i<len-1;i++)
    {
        if(axis[point].y>=0.1)
        {
            peak[k].x=axis[point].x;
            peak[k].y=axis[point].y;
            printf("%lf\t%lf\n",peak[k].x,peak[k].y);
            point++;
            k++;
            flag++;
        }
        else if(axis[point].y<0.1)
        {
            if(flag>1)
            break;
            else
            point++;
        }
    }
}
int main()
{
    FILE *fp;
    int i,j;
    fp=fopen("test.txt","r");
    if(fp==NULL)
    printf("File not found!");
    int len;
    //reading datalength
    fseek(fp,16,SEEK_SET);
    fscanf(fp,"%d",&len);
    printf("%d\n",len);

    double a[len],b[len];
    
    //reading x
    fseek(fp,54,SEEK_SET);
    for(i=0;i<len;i++)
    {
        fscanf(fp,"%lf",&a[i]);
        //printf("%lf\n",a[i]);
        fseek(fp,18,SEEK_CUR);
    }
    
    //reading y
    fseek(fp,70,SEEK_SET);
    for(j=0;j<len;j++)
    {
        fscanf(fp,"%lf",&b[j]);
        //printf("%lf\n",b[j]);
        fseek(fp,18,SEEK_CUR); 
    }
    struct plot axis[len];
    for(int k=0;k<len;k++)
    {
        axis[k].x=a[k];
        axis[k].y=b[k];
        //printf("%lf\t%lf\n",axis[k].x,axis[k].y);
    }
    fclose(fp);
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

        DrawScatterPlot(imageRef, 1250, 800, a, 10000, b, 10000);

        size_t length;
        double *pngData = ConvertToPNG(&length, imageRef->image);
        WriteToFile(pngData, length, "plot.png");

       
    struct plot *peak1=(struct plot*)malloc(sizeof(struct plot));
    while(point<len-1)
    {
        group(peak1,len,axis);
        printf("\n");
    }
    free(axis);
    free(peak1);
     return 0;
}
