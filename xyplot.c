#include "pbPlots.c"
#include "supportLib.c"
#include <stdio.h>
#include<stdlib.h>
int main()
{
    FILE *fp;
    fp=fopen("test.txt","r");
    if(fp==NULL)
         printf("File not found!");
    fseek(fp,16,SEEK_SET);

    int len;
    fscanf(fp,"%d",&len);
    printf("Data length:%d\n",len);
    double x[len],y[len];

    fseek(fp,54,SEEK_SET);

    for(int i=0;i<len;i++)
    {
        fscanf(fp,"%lf",&x[i]);
        printf("%lf\n",x[i]);
        fseek(fp,18,SEEK_CUR);
    }
    fseek(fp,70,SEEK_SET);

    for(int j=0;j<len;j++)
    {
       fscanf(fp,"%lf",&y[j]);
       printf("%lf\n",y[j]);
       fseek(fp,18,SEEK_CUR);
    }
    free(x);
    free(y);
    fclose(fp);
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

        DrawScatterPlot(imageRef, 1250, 800, x, 10000, y, 10000);

        size_t length;
        double *pngData = ConvertToPNG(&length, imageRef->image);
        WriteToFile(pngData, length, "plot.png");

        return 0;
 
}