#include "pbPlots.c"
#include "supportLib.c"
#include<stdio.h>
#include<stdlib.h>
int point=0;   //for accessing all the time and intensity values
struct plot
{
    double x,y;
};
int group(struct plot peak[100],int len,struct plot axis[len])
{
    int k=0;    //k for index of peak
    double part1,part2=0,area;
    double h=axis[1].x-axis[0].x;       //h=t2-t1
    for(int i=0;i<len-1;i++)
    {
        if(point!=len)
        {
            if(axis[point].y>=0.1)   //checks intensity >=0.1
            {
                peak[k].x=axis[point].x; 
                peak[k].y=axis[point].y;  //copying values to peak(array of structure)
                point++;
                k++;
            }
            else if(axis[point].y<0.1)  //checks intensity <0.1
            {
                if(k<2)
                {
                    point++;
                    k=0;
                }
                else if(k>=2)
                {
                    part1=peak[0].y+peak[k-1].y;         
                    for(int j=1;j<=k-2;j++)
                    {
                        //printf("%lf\n",peak[j].y);
                        part2=part2+peak[j].y;
                    }
                    area=((h*0.5)*(part1+2*part2));   //area
                    printf("n : %d\tArea : %lf\n",k,area);
                    break;
                }
            }
        }
    }
    for(int l=0;l<=k-1;l++)
    {
        printf("%lf\t%lf\n",peak[l].x,peak[l].y);  //points of peak
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

    double *a=(double *)malloc(len*sizeof(double));
    double *b=(double *)malloc(len*sizeof(double));;
    struct plot *axis=(struct plot*)malloc(len*sizeof(struct plot));//declaring array of structure

    //reading x
    fseek(fp,54,SEEK_SET);
    for(i=0;i<len;i++)
    {
        fscanf(fp,"%lf",&a[i]);
        //printf("%lf\n",a[i]);
        axis[i].x=a[i];        //copying to a array of structure
        fseek(fp,18,SEEK_CUR);
    }
    //reading y
    fseek(fp,70,SEEK_SET);
    for(j=0;j<len;j++)
    {
        fscanf(fp,"%lf",&b[j]);
        //printf("%lf\n",b[j]);
        axis[j].y=b[j];           //copying to a array of structure
        fseek(fp,18,SEEK_CUR); 
    }
    fclose(fp);

    /*RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    DrawScatterPlot(imageRef, 1250, 800, a, 10000, b, 10000);
    size_t length;
    double *pngData = ConvertToPNG(&length, imageRef->image);
    WriteToFile(pngData, length, "plot.png");*/

    struct plot *peak=(struct plot*)malloc(len*sizeof(struct plot));//memory allocation using malloc
    while(point<len)
    {
        group(peak,len,axis);
        printf("\n"); 
    }
    free(axis);
    free(peak);
}