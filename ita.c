#include "pbPlots.c"
#include "supportLib.c"
#include<stdio.h>
#include<stdlib.h>
int point=0;
struct plot
{
    double x,y;
};
int group(struct plot peak[100],int len,struct plot axis[len])
{
    int k=0;   
    double part1,part2=0,area;
    double h=axis[1].x-axis[0].x;       
    for(int i=0;i<len-1;i++)
    {
        if(point!=len)
        {
            if(axis[point].y>=0.1)   
            {
                peak[k].x=axis[point].x; 
                peak[k].y=axis[point].y;  
                point++;
                k++;
            }
            else if(axis[point].y<0.1)  
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
                    area=((h*0.5)*(part1+2*part2));  
                    printf("n : %d\tArea : %lf\n",k,area);
                    break;
                }
            }
        }
    }
    for(int l=0;l<=k-1;l++)
    {
        printf("%lf\t%lf\n",peak[l].x,peak[l].y);  
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
    double *b=(double *)malloc(len*sizeof(double));
    struct plot *axis=(struct plot*)malloc(len*sizeof(struct plot));

    //reading x
    fseek(fp,54,SEEK_SET);
    for(i=0;i<len;i++)
    {
        fscanf(fp,"%lf",&a[i]);
        //printf("%lf\n",a[i]);
        axis[i].x=a[i];        
        fseek(fp,18,SEEK_CUR);
    }
    //reading y
    fseek(fp,70,SEEK_SET);
    for(j=0;j<len;j++)
    {
        fscanf(fp,"%lf",&b[j]);
        //printf("%lf\n",b[j]);
        axis[j].y=b[j];           
        fseek(fp,18,SEEK_CUR); 
    }
    fclose(fp);

    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    DrawScatterPlot(imageRef, 1250, 800, a, len, b, len);
    size_t length;
    double *pngData = ConvertToPNG(&length, imageRef->image);
    WriteToFile(pngData, length, "plot.png");
    free(a);
    free(b);

    struct plot *peak=(struct plot*)malloc(len*sizeof(struct plot));
    while(point<len)
    {
        group(peak,len,axis);
        printf("\n"); 
    }
    free(axis);
    free(peak);
}
