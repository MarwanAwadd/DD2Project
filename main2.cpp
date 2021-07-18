int viaCount;
int viaCost=10;
int **board;
int boardW;
int boardH;
vector <int> OBSx;
vector <int> OBSy;
struct net{
    string netLine;
    string name;
    vector<int> metal;
    vector<int> pinX;
    vector<int> pinY;
};
vector<net> nets;


net setupNet(net currNet){
    stringstream netLineSS;
    netLineSS << currNet.netLine;
    int i = 0;
    string temp;
    
    while(netLineSS >> temp){
        if(i != 0){
            string pin;
            string pinMetal;
            string pinX;
            string pinY;

            pin = temp;

            pin = pin.substr(1, pin.find(')') - 1);
            pinMetal = pin.substr(0, pin.find(','));

            pin = pin.substr(pin.find(',') + 1);
            pinX = pin.substr(0, pin.find(','));

            pinY = pin.substr(pin.find(',') + 1);

            currNet.metal.push_back(stoi(pinMetal));
            currNet.pinX.push_back(stoi(pinX));
            currNet.pinY.push_back(stoi(pinY));
        }

        else
            currNet.name = temp;
        i++;
    }
    
    return currNet;
}


void layer1(int x, int y, int** metal1, int M, int N, int smallest_value) {


    int	new_x_value = metal1[y][x] + 1;// horizontal: cost = 1
    int	new_y_value = metal1[y][x] + 10; //vertical: cost of via = 10
	//left top edge
	if (x == 0 && y == 0) {
		//check the right cell
		if (metal1[y][x + 1] == smallest_value + 1 || new_x_value < metal1[y][x + 1]) // if new value greater than the current value
		{
			metal1[y][x + 1] = new_x_value;  // assign the new value in to the array
			layer1(x + 1, y, metal1, M, N, smallest_value); // call the function recursively
		}
		//check the below cell
		if (metal1[y + 1][x] == smallest_value + 1 || new_y_value < metal1[y + 1][x]) {
			metal1[y + 1][x] = new_y_value;
			layer1(x, y + 1, metal1, M, N, smallest_value ); // call the function recursively
		}
		
	}
	//right bottom edge
	else if (x == M - 1 && y == N - 1) {
		//check the left cell
		if (metal1[y][x - 1] == smallest_value + 1 || new_x_value < metal1[y][x - 1]) // if new value greater than the current value
		{
			metal1[y][x - 1] = new_x_value; // assign the new value in to the array
			layer1(x - 1, y, metal1, M, N, smallest_value); // call the function recursively
		}
		//check the above cell
		if (metal1[y - 1][x] == smallest_value + 1 || new_y_value < metal1[y - 1][x]) // if new value greater than the current value
		{
			metal1[y - 1][x] = new_y_value; // assign the new value in to the array
			layer1(x, y - 1, metal1, M, N, smallest_value); // call the function recursively
		}
	}
	//right top edge
	else if (x == M - 1 && y == 0) {
		//check the left cell
		if (metal1[y][x - 1] == smallest_value + 1 || new_x_value < metal1[y][x - 1]) // if new value greater than the current value
		{
			metal1[y][x - 1] = new_x_value; // assign the new value in to the array
			layer1(x - 1, y, metal1, M, N, smallest_value); // call the function recursively
		}
		//check the below cell
		if (metal1[y + 1][x] == smallest_value + 1 || new_y_value < metal1[y + 1][x]) {
			metal1[y + 1][x] = new_y_value;
			layer1(x, y + 1, metal1, M, N, smallest_value);// call the function recursively
		}
	}
	//left bottom edge
	else if (x == 0 && y == N - 1) {
		//check the right cell
		if (metal1[y][x + 1] == smallest_value + 1 || new_x_value < metal1[y][x + 1]) // if new value greater than the current value
		{
			metal1[y][x + 1] = new_x_value; // assign the new value in to the array
			layer1(x + 1, y, metal1, M, N, smallest_value); // call the function recursively
		}
		//check the top cell
		if (metal1[y - 1][x] == smallest_value + 1 || new_y_value < metal1[y - 1][x]) // if new value greater than the current value
		{
			metal1[y - 1][x] = new_y_value; // assign the new value in to the array
			layer1(x, y - 1, metal1, M, N, smallest_value); // call the function recursively
		}
	}
	//left of the grid
	else if (x == 0) {
		//check the right cell
		if (metal1[y][x + 1] == smallest_value + 1 || new_x_value < metal1[y][x + 1]) // if new value greater than the current value
		{
			metal1[y][x + 1] = new_x_value; // assign the new value in to the array
			layer1(x + 1, y, metal1, M, N, smallest_value); // call the function recursively
		}
		//check the top cell
		if (metal1[y - 1][x] == smallest_value + 1 || new_y_value < metal1[y - 1][x]) 
		{
			metal1[y - 1][x] = new_y_value;
			layer1(x, y - 1, metal1, M, N, smallest_value); // call the function recursively
		}
		//check the bottom cell
		if (metal1[y + 1][x] == smallest_value + 1 || new_y_value < metal1[y + 1][x]) // if new value greater than the current value
		{
			metal1[y + 1][x] = new_y_value; // assign the new value in to the array
			layer1(x, y + 1, metal1, M, N, smallest_value); // call the function recursively
		}

	}
	//right of the grid
	else if (x == M - 1) {
		//check the left cell
		if (metal1[y][x - 1] == smallest_value + 1 || new_x_value < metal1[y][x - 1]) // if new value greater than the current value
		{
			metal1[y][x - 1] = new_x_value; // assign the new value in to the array
			layer1(x - 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal1[y - 1][x] == smallest_value + 1 || new_y_value < metal1[y - 1][x]) // if new value greater than the current value
		{
			metal1[y - 1][x] = new_y_value;// assign the new value in to the array
			layer1(x, y - 1, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal1[y + 1][x] == smallest_value + 1 || new_y_value < metal1[y + 1][x]) // if new value greater than the current value
		{
			metal1[y + 1][x] = new_y_value;// assign the new value in to the array
			layer1(x, y + 1, metal1, M, N, smallest_value);// call the function recursively
		}
	}
	//top of the grid
	else if (y == 0) {
		//check the left cell
		if (metal1[y][x - 1] == smallest_value + 1 || new_x_value < metal1[y][x - 1]) {
			metal1[y][x - 1] = new_x_value;
			layer1(x - 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the right cell
		if (metal1[y][x + 1] == smallest_value + 1 || new_x_value < metal1[y][x + 1]) {
			metal1[y][x + 1] = new_x_value;
			layer1(x + 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal1[y + 1][x] == smallest_value + 1 || new_y_value < metal1[y + 1][x]) {
			metal1[y + 1][x] = new_y_value;
			layer1(x, y + 1, metal1, M, N, smallest_value);// call the function recursively
		}
	}
	//bottom of the grid
	else if (y == N - 1) {
		//check the left cell
		if (metal1[y][x - 1] == smallest_value + 1 || new_x_value < metal1[y][x - 1]) {
			metal1[y][x - 1] = new_x_value;
			layer1(x - 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the right cell
		if (metal1[y][x + 1] == smallest_value + 1 || new_x_value < metal1[y][x + 1]) {
			metal1[y][x + 1] = new_x_value;
			layer1(x + 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal1[y - 1][x] == smallest_value + 1 || new_y_value < metal1[y - 1][x]) {
			metal1[y - 1][x] = new_y_value;
			layer1(x, y - 1, metal1, M, N, smallest_value);// call the function recursively
		}
	}
	//middle of the grid
	else {
		//check the left cell
		if (metal1[y][x - 1] == smallest_value + 1 || new_x_value < metal1[y][x - 1]) {
			metal1[y][x - 1] = new_x_value;
			layer1(x - 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the right cell
		if (metal1[y][x + 1] == smallest_value + 1 || new_x_value < metal1[y][x + 1]) {
			metal1[y][x + 1] = new_x_value;
			layer1(x + 1, y, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal1[y - 1][x] == smallest_value + 1 || new_y_value < metal1[y - 1][x]) {
			metal1[y - 1][x] = new_y_value;
			layer1(x, y - 1, metal1, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal1[y + 1][x] == smallest_value + 1 || new_y_value < metal1[y + 1][x]) {
			metal1[y + 1][x] = new_y_value;
			layer1(x, y + 1, metal1, M, N, smallest_value);// call the function recursively
		}
	}
}


void layer2(int x, int y, int** metal1, int** metal2, int M, int N, int smallest_value) {

	int new_y_value = metal2[y][x] + 1; // increment the cost by 1 in vertical dirction since it is legal the direction
	int new_x_value = metal2[y][x] + 10;// increment the cost by 10 in vertical dirction since it is illegal the direction

	//left top edge
	if (x == 0 && y == 0) {
		//check the right cell
		if (metal2[y][x + 1] == smallest_value + 1 || new_x_value < metal2[y][x + 1] || ((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1)) {
			metal2[y][x + 1] = new_x_value;
			if (((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value

				metal2[y][x + 1] = metal1[y][x + 1] + viaCost;
			layer2(x + 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the below cell
		if (metal2[y + 1][x] == smallest_value + 1 || new_y_value < metal2[y + 1][x] || ((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y+1][x] != -1)) {
			metal2[y + 1][x] = new_y_value;

		if (((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
			metal2[y + 1][x] = metal1[y + 1][x] + viaCost;

			layer2(x, y + 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}

	}
	//right bottom edge
	else if (x == M - 1 && y == N - 1) {
		//check the left cell
		if (metal2[y][x - 1] == smallest_value + 1 || new_x_value < metal2[y][x - 1] || ((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1)) {
			metal2[y][x - 1] = new_x_value;

			if (((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x - 1] = metal1[y][x - 1] + viaCost;

			layer2(x - 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the above cell
		if (metal2[y - 1][x] == smallest_value + 1 || new_y_value < metal2[y - 1][x] || ((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y-1][x] != -1)) {
			metal2[y - 1][x] = new_y_value;
			
			if (((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y - 1][x] = metal1[y - 1][x] + viaCost;

			layer2(x, y - 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
	//right top edge
	else if (x == M - 1 && y == 0) {
		//check the left cell
		if (metal2[y][x - 1] == smallest_value + 1 || new_x_value < metal2[y][x - 1] || ((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1)) {
			metal2[y][x - 1] = new_x_value;
			if (((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x - 1] = metal1[y][x - 1] + viaCost;
			layer2(x - 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the below cell
		if (metal2[y + 1][x] == smallest_value + 1 || new_y_value < metal2[y + 1][x] || ((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1)) {
			metal2[y + 1][x] = new_y_value;

			if (((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y + 1][x] = metal1[y + 1][x] + viaCost;

			layer2(x, y + 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
	//left bottom edge
	else if (x == 0 && y == N - 1) {
		//check the right cell
		if (metal2[y][x + 1] == smallest_value + 1 || new_x_value < metal2[y][x + 1] || ((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1)) {
			metal2[y][x + 1] = new_x_value;
			if (((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x + 1] = metal1[y][x + 1] + viaCost;
			layer2(x + 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal2[y - 1][x] == smallest_value + 1 || new_y_value < metal2[y - 1][x] || ((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1)) {
			metal2[y - 1][x] = new_y_value;

			if (((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y - 1][x] = metal1[y - 1][x] + viaCost;

			layer2(x, y - 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
	//left of the grid
	else if (x == 0) {
		//check the right cell
		if (metal2[y][x + 1] == smallest_value + 1 || new_x_value < metal2[y][x + 1] || ((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1)) {
			metal2[y][x + 1] = new_x_value;
			if (((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x + 1] = metal1[y][x + 1] + viaCost;
			layer2(x + 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal2[y - 1][x] == smallest_value + 1 || new_y_value < metal2[y - 1][x] || ((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1)) {
			metal2[y - 1][x] = new_y_value;

			if (((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y - 1][x] = metal1[y - 1][x] + viaCost;

			layer2(x, y - 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal2[y + 1][x] == smallest_value + 1 || new_y_value < metal2[y + 1][x] || ((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1)) {
			metal2[y + 1][x] = new_y_value;

			if (((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y + 1][x] = metal1[y + 1][x] + viaCost;

			layer2(x, y + 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}

	}
	//right of the grid
	else if (x == M - 1) {
		//check the left cell
		if (metal2[y][x - 1] == smallest_value + 1 || new_x_value < metal2[y][x - 1] || ((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1)) {
			metal2[y][x - 1] = new_x_value;
			if (((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x - 1] = metal1[y][x - 1] + viaCost;
			layer2(x - 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal2[y - 1][x] == smallest_value + 1 || new_y_value < metal2[y - 1][x] || ((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1)) {
			metal2[y - 1][x] = new_y_value;

			if (((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y - 1][x] = metal1[y - 1][x] + viaCost;

			layer2(x, y - 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal2[y + 1][x] == smallest_value + 1 || new_y_value < metal2[y + 1][x] || ((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1)) {
			metal2[y + 1][x] = new_y_value;

			if (((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y + 1][x] = metal1[y + 1][x] + viaCost;

			layer2(x, y + 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
	//top of the grid
	else if (y == 0) {
		//check the left cell
		if (metal2[y][x - 1] == smallest_value + 1 || new_x_value < metal2[y][x - 1] || ((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1)) {
			metal2[y][x - 1] = new_x_value;
			if (((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x - 1] = metal1[y][x - 1] + viaCost;
			layer2(x - 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the right cell
		if (metal2[y][x + 1] == smallest_value + 1 || new_x_value < metal2[y][x + 1] || ((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1)) {
			metal2[y][x + 1] = new_x_value;
			if (((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x + 1] = metal1[y][x + 1] + viaCost;
			layer2(x + 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal2[y + 1][x] == smallest_value + 1 || new_y_value < metal2[y + 1][x] || ((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1)) {
			metal2[y + 1][x] = new_y_value;

			if (((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y + 1][x] = metal1[y + 1][x] + viaCost;

			layer2(x, y + 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
	//bottom of the grid
	else if (y == N - 1) {
		//check the left cell
		if (metal2[y][x - 1] == smallest_value + 1 || new_x_value < metal2[y][x - 1] || ((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1)) {
			metal2[y][x - 1] = new_x_value;
			if (((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x - 1] = metal1[y][x - 1] + viaCost;
			layer2(x - 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the right cell
		if (metal2[y][x + 1] == smallest_value + 1 || new_x_value < metal2[y][x + 1] || ((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1)) {
			metal2[y][x + 1] = new_x_value;
			if (((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x + 1] = metal1[y][x + 1] + viaCost;
			layer2(x + 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal2[y - 1][x] == smallest_value + 1 || new_y_value < metal2[y - 1][x] || ((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1)) {
			metal2[y - 1][x] = new_y_value;

			if (((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y - 1][x] = metal1[y - 1][x] + viaCost;

			layer2(x, y - 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
	//middle of the grid
	else {
		//check the left cell
		if (metal2[y][x - 1] == smallest_value + 1 || new_x_value < metal2[y][x - 1] || ((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1)) {
			metal2[y][x - 1] = new_x_value;
			if (((metal1[y][x - 1] + viaCost) < metal2[y][x - 1] && metal1[y][x - 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x - 1] = metal1[y][x - 1] + viaCost;
			layer2(x - 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the right cell
		if (metal2[y][x + 1] == smallest_value + 1 || new_x_value < metal2[y][x + 1] || ((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1)) {
			metal2[y][x + 1] = new_x_value;
			if (((metal1[y][x + 1] + viaCost) < metal2[y][x + 1] && metal1[y][x + 1] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y][x + 1] = metal1[y][x + 1] + viaCost;
			layer2(x + 1, y, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the top cell
		if (metal2[y - 1][x] == smallest_value + 1 || new_y_value < metal2[y - 1][x] || ((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1)) {
			metal2[y - 1][x] = new_y_value;

			if (((metal1[y - 1][x] + viaCost) < metal2[y - 1][x] && metal1[y - 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y - 1][x] = metal1[y - 1][x] + viaCost;

			layer2(x, y - 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
		//check the bottom cell
		if (metal2[y + 1][x] == smallest_value + 1 || new_y_value < metal2[y + 1][x] || ((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1)) {
			metal2[y + 1][x] = new_y_value;

			if (((metal1[y + 1][x] + viaCost) < metal2[y + 1][x] && metal1[y + 1][x] != -1))// It checks the value produced by the equation is greater the other value which is the sum of the fill cost of layer below + via cost if yes reassign it with other value
				metal2[y + 1][x] = metal1[y + 1][x] + viaCost;

			layer2(x, y + 1, metal1, metal2, M, N, smallest_value);// call the function recursively
		}
	}
}

void readInput(string file){
    fstream testFile;
    testFile.open("Tests/"+file);
    if (testFile.is_open()){   //checking whether the file is open
        cout << "open" << endl;
        string tp;
        while(getline(testFile, tp)){
            stringstream line;
            line << tp;
            string firstWord;
            line >> firstWord;
            if(firstWord.find("net") != string::npos){
                net currNet;
                currNet.netLine = tp;
                currNet = setupNet(currNet);
                nets.push_back(currNet);
            }
            else if(firstWord.find("OBS") != string::npos){
                string OBSph, OBSxs, OBSys;
                stringstream obs;
                obs << tp;
                obs >> OBSph >> OBSxs >> OBSys;
                OBSy.push_back(stoi(OBSys));
                OBSx.push_back(stoi(OBSxs));
            }
            else if ((firstWord.find("1") != string::npos) || (firstWord.find("2") != string::npos)){
                
            }
            else{
                string w, h;
                int i = 0;
                while(tp[i] != 'x'){
                    w = w + tp[i];
                    i++;
                }
                tp = tp.substr(i + 1);
                h = tp;
                boardW = stoi(w);
                boardH = stoi(h);
            }
        }
        testFile.close();
   }


}

void initBoard(string fileName){
    readInput(fileName);
    
    //Iniitialize empty board as 2d array
    board = new int*[boardH];
    for(int i = 0; i < boardH; i++){
        board[i] = new int[boardW];
    }
    
    for(int i = 0; i < boardH; i++){
        for(int j = 0; j < boardW; j++){
            board[i][j] = 0;
        }
    }
    
    for(int i = 0; i < OBSx.size(); i++){
        board[OBSy[i] - 1][OBSx[i] - 1] = -1;
    }
    
    for(int i = 0; i < nets.size(); i++){
        for(int j = 0; j < nets[i].metal.size(); j++){
            board[nets[i].pinY[j] - 1][nets[i].pinX[j] - 1] = i + 1;
        }
    }
    
    for(int i = 0; i < boardH; i++){
        for(int j = 0; j < boardW; j++){
            cout << board[i][j] << "   ";
        }
        cout << endl;
    }
    
}

int main(){
    initBoard("test1.txt");
    return 0;
}
