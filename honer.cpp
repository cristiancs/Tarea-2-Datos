#include<iostream>
#include<iomanip>

using namespace std;


float horner(float A[],int d ,float x) 
{               double r;
                int i;
                r=A[d];
                i=d-1;
                while (i>=0)
		r = A[i--] + r * x;
                return r;

        } 

int main()
{
          float *coefficients,*A0,*A1,A0X,A1X, f_xo1,f_xo2;;                //Pointer to an array of real numbers
          int    degree, i,k, n,x0,z;                                        // degree of polynomial    
                               
           
     
          cout << "Degree of polynomial: ";
          cin >> degree;    
          
         //Dynamically allocate memory large enough to hold array of coefficients of polynomial
          coefficients = new float[degree+1];
                  
       
        cout << "Enter coefficients : \n";//entering the coefficients of polynomial
        
        for(i = degree; i > -1; i--)
        {
              
                cin >> coefficients[i];
                
        }
                
         //prints the polynomial      
         
         cout<<"f(x)= ";
         
         for(i=degree;i>=0;i--)
         {
                if(i==0)
                
                  cout<<coefficients[i]<<"x^"<<i;
                  
                else
                
                  cout<<coefficients[i]<<"x^"<<i<<" + ";  
         
         }
          
         cout<<endl<<endl;
     
	 if((degree+1) % 2) 
           
             A0 = new float[ (degree+1) / 2 + 1];
            
         else
           
             A0 = new float[(degree+1) / 2];
                               
		
       A1 = new float[(degree+1) / 2];
            
        
       for(i=0 ; i<=degree ;  i += 2 )
       { 
               
            A0[i]=coefficients[i];
            
            A1[i + 1]=coefficients[i + 1]; 
            
       }		
		
            if((degree+1) % 2 != 0)       
		
		A0[(degree+1) / 2 + 1] = coefficients[degree];
              
       
	   cout << "Evaluate polynomial at x0 = ";
           cin  >> x0; 
       
           cout<<endl;
	   
	     
	   A0X = horner(A0,degree ,x0);
	   
	   A1X = horner(A1,degree, x0);
	   
	   f_xo1 = A0X + x0 * A1X;		  
	   
	   cout<<" -  (x0,f(x0)  : ("<<x0<<" , "<<f_xo1<<" )"<<endl<<endl;
	   
	   f_xo2 = A0X - x0 * A1X;	   
	   
	   cout<<" -  (-x0,f(-x0)  : ( -"<<x0<<" , "<<f_xo2<<" )"<<endl<<endl;
   
        
system("pause");   
return 0;
}

