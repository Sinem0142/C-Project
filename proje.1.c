#include<stdio.h>
int main(){
	int supplierCode;
	int product;
	int total1=0;
	int total2=0;
	int total3=0;
	int grandTotal=0;
	int largest;
	int i;
	int numProducts;
	
	
	printf("Enter -1 for supplier code to exit the program:\n");
	printf("Enter supplier code: ");
	scanf("%d" , &supplierCode);
	while(supplierCode!=-1){
		while(supplierCode!=1 && supplierCode!=2 && supplierCode!=3){
			printf("Incorrect supplier code!");
                     	printf("Enter supplier code: ");
                     	scanf("%d" , &supplierCode);
			
		}
		if(supplierCode==1){
			printf("How many different products did supplier 1 bring today:");
			scanf("%d" , &numProducts);
			for(i=0 ; i<numProducts ; i++){
				printf("Enter quantity of product %d:" , i+1);
				scanf("%d" , &product);
				total1=total1+product;
			}
		}
		else if(supplierCode==2){
			printf("How many different products did supplier 2 bring today:");
			scanf("%d" , &numProducts);
			for(i=0 ; i<numProducts ; i++){
				printf("Enter quantity of product %d:" , i+1);
				scanf("%d" , &product);
				total2=total2+product;
			}
		}
		else if(supplierCode==3){
			printf("How many different products did supplier 3 bring today:");
			scanf("%d" , &numProducts);
			for(i=0 ; i<numProducts ; i++){
				printf("Enter quantity of product %d:" , i+1);
				scanf("%d" , &product);
				total3=total3+product;
			}
		}
		printf("Enter supplier code: ");
                    scanf("%d" , &supplierCode);
		
	}
	grandTotal=total1+total2+total3;
	if(total1>=total2 && total1>=total3){
		largest=total1;
	}
	else if(total2>=total1 && total2>=total3){
		largest=total2;
	}
	else if(total3>=total2 && total3>=total1){
		largest=total3;
	}
	
	printf("--------------------------------\n");
	printf("Total number of products received: %d \n" , grandTotal);
	printf("Supplier with the most products sent in one go and the quantity sent:");
	if(total1>=total2 && total1>=total3){
		largest=total1;
		printf("Supplier ABC (%d units)" , largest);
	}
	else if(total2>=total1 && total2>=total3){
		largest=total2;
		printf("Supplier XYZ (%d units)" , largest);
	}
	else if(total3>=total2 && total3>=total1){
		largest=total3;
		printf("Supplier BIL (%d units)" , largest);
	}
	return 0;
}
