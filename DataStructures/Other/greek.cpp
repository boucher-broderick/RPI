#include <vector>
#include <iostream>

void print(std::vector<std::vector<std::vector<int>>> const &levels){
	for(int pos = 0; pos < 12; pos++){				// Rotates the position for each layer
		int sum =0;
		for(int x = 0; x < 4; x++){
			int layers=x;
			int lay = levels[layers].size()-(x+1);
			int temp =levels[layers][lay][pos];
			
			while(temp==0){
				layers++;
				if(layers!=4){
					lay++;
				}
				temp=levels[layers][lay][pos];

			}
			std::cout << temp << "-";
			sum+=temp;
		}
		std::cout << sum ;
		std::cout << std::endl;

	}
	
}



//CHECK IS FUCKED SAME WITH PRINT


bool check(std::vector<std::vector<std::vector<int>>> const &levels){
	

	for(int pos = 0; pos < 12; pos++){				// Rotates the position for each layer
		int sum =0;
		for(int x = 0; x < 4; x++){
			int layers=x;
			int lay = levels[layers].size()-(x+1);
			int temp =levels[layers][lay][pos];
			
			while(temp==0){
				layers++;
				if(layers!=4){
					lay++;
				}
				temp=levels[layers][lay][pos];

			}
			//std::cout << temp << " ";
			sum+=temp;
		}
		//std::cout << sum << std::endl; 
		if(sum!=42){
			//std::cout << "fail" << std::endl; 
			return false;
		}
		

	}
	
	return true;
	
}


bool check1(std::vector<std::vector<std::vector<int>>> &levels){
	for(int pos = 0; pos < 12; pos++){
		bool ans = check(levels);
		//std::cout << "\t\t\tcheck1:  ";
		//print(levels);
		if(ans){
			return true;
			std::cout << "true" << std::endl;
		}
		else{
			//std::cout << levels[0][0][0] << "fail" << std::endl;
			int layers =levels[0].size();
			for(int x =0; x < layers; x++){
				int temp = levels[0][x][0];
				levels[0][x].erase(levels[0][x].begin());
				levels[0][x].push_back(temp);
			}
		}
	}
	return false;
}

bool check2(std::vector<std::vector<std::vector<int>>> &levels){
	for(int pos = 0; pos < 12; pos++){
		bool ans = check1(levels);
		//std::cout << "\t\tcheck2: ";
		//print(levels);
		
		if(ans){
			return true;
			std::cout << "true" << std::endl;
		}
		else{
			//std::cout << levels[1][0][0] << "fail" << std::endl;
			int layers =levels[1].size();
			for(int x =0; x < layers; x++){
				int temp = levels[1][x][0];
				levels[1][x].erase(levels[1][x].begin());
				levels[1][x].push_back(temp);
			}
		}
	}
	return false;
}

bool check3(std::vector<std::vector<std::vector<int>>> &levels){
	for(int pos = 0; pos < 12; pos++){
		bool ans = check2(levels);
		//std::cout << "\tcheck3: ";
		//print(levels);
		
		if(ans){
			return true;
			std::cout << "true" << std::endl;
		}
		else{
			//std::cout << levels[2][0][0] << "fail" << std::endl;
			int layers =levels[2].size();
			for(int x =0; x < layers; x++){
				int temp = levels[2][x][0];
				levels[2][x].erase(levels[2][x].begin());
				levels[2][x].push_back(temp);
			}
		}
	}
	return false;
}

bool check4(std::vector<std::vector<std::vector<int>>> &levels){
	for(int pos = 0; pos < 12; pos++){
		bool ans = check3(levels);
		//print(levels);
		//std::cout << std::endl;
		if(ans){
			return true;
			std::cout << "true" << std::endl;
		}
		else{
			//std::cout << levels[3][0][0] << "fail" << std::endl;
			int layers =levels[3].size();
			for(int x =0; x < layers; x++){
				int temp = levels[3][x][0];
				levels[3][x].erase(levels[3][x].begin());
				levels[3][x].push_back(temp);
			}
		}
	}
	return false;
}

bool check5(std::vector<std::vector<std::vector<int>>> &levels){
	for(int pos = 0; pos < 12; pos++){
		bool ans = check4(levels);
		if(ans){
			return true;
			std::cout << "true" << std::endl;
		}
		else{
		//	std::cout << levels[4][0][0] << levels[4][1][0] << " 5 fail" << std::endl;
			int layers =levels[4].size();
			for(int x =0; x < layers; x++){
				int temp = levels[4][x][0];
				levels[4][x].erase(levels[4][x].begin());
				levels[4][x].push_back(temp);
			}
		}
	}
	return false;
}

int main(){
	std::vector<int> L1L1 { 7, 0, 15, 0, 8, 0, 3, 0, 6, 0, 10, 0};    //Level1 Layer1
	std::vector<int> L2L1 { 14, 0, 9, 0, 12, 0, 4, 0, 7, 15, 0, 0};   //Level2 Layer1
	std::vector<int> L2L2 { 11, 6, 11, 0, 6, 17, 7, 3, 0, 6, 0, 11};  //Level2 Layer2
	std::vector<int> L3L1 { 9, 0, 5, 0, 10, 0, 8, 0, 22, 0, 16, 0};
	std::vector<int> L3L2 { 12, 0, 21, 6, 15, 4, 9, 18, 11, 26, 14, 1};
	std::vector<int> L3L3 { 7, 8, 9, 13, 9, 7, 13, 21, 17, 4, 5, 0};
	std::vector<int> L4L1 { 6, 0, 10, 0, 10, 0, 1, 0, 9, 0, 12, 0};
	std::vector<int> L4L2 { 9, 0, 17, 19, 3, 12, 3, 26, 6, 0, 2, 13};
	std::vector<int> L4L3 { 14, 12, 3, 8, 9, 9, 0, 20, 12, 3, 6, 0};
	std::vector<int> L4L4 { 11, 0, 8, 0, 16, 2, 7, 0, 9, 0, 7, 14};
	std::vector<int> L5L1 { 3, 4, 12, 2, 5, 10, 7, 16, 8, 7, 8, 8};
	std::vector<int> L5L2 { 4, 6, 6, 3, 3, 14, 14, 21, 21, 9, 9, 4};
	std::vector<int> L5L3 { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 4};
	std::vector<int> L5L4 { 11, 14, 11, 14, 11, 14, 14, 11, 14, 11, 14, 11};

	std::vector<std::vector<int>> layer1;
	layer1.push_back(L1L1);
	std::vector<std::vector<int>> layer2;
	layer2.push_back(L2L1);
	layer2.push_back(L2L2);
	std::vector<std::vector<int>> layer3;
	layer3.push_back(L3L1);
	layer3.push_back(L3L2);
	layer3.push_back(L3L3);
	std::vector<std::vector<int>> layer4;
	layer4.push_back(L4L1);
	layer4.push_back(L4L2);
	layer4.push_back(L4L3);
	layer4.push_back(L4L4);
	std::vector<std::vector<int>> layer5;
	layer5.push_back(L5L1);
	layer5.push_back(L5L2);
	layer5.push_back(L5L3);
	layer5.push_back(L5L4);

	std::vector<std::vector<std::vector<int>>> levels;
	levels.push_back(layer1);
	levels.push_back(layer2);
	levels.push_back(layer3);
	levels.push_back(layer4);
	levels.push_back(layer5);


	if(check5(levels)){
		print(levels);
	}

	/* 
	//Tests the number of layers:
	std::cout  << levels[0].size() << std::endl;
	std::cout  << levels[1].size() << std::endl;
	std::cout  << levels[2].size() << std::endl;
	std::cout  << levels[3].size() << std::endl;
	std::cout  << levels[4].size() << std::endl;
	
	//Tests erase and add to back:
	int temp = levels[0][0][0];
	levels[0][0].erase(levels[0][0].begin());
	std::cout << temp << " " << levels[0][0][0] << std::endl;

	//Refresher for how the levels works:
	std::cout << levels.size() << " " << levels[1].size() << " " << levels[1][0].size() <<std::endl;
	
	//Tests Check:
	check(levels);

    //*/
	

};