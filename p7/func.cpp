size_t FindeNextMinDuration(dynamicArray<T> &array, meetingData &minDuration){

    bool flag = false;
    int indexOfNewMinData = 0;
   
    if(minDuration.visited) {
        for (int index = 0; index < array.size; ++index) {
            if(!array.buffer[index].visited)
            {
              return  FindeNextMinDuration(array, array.buffer[index]);
            }
        }
    }
    else   if (!minDuration.visited) {
        for (int ind = 0; ind < array.size; ++ind) {
            if (array.buffer[ind].duration < minDuration.duration &&
                array.buffer[ind].duration && !array.buffer[ind].visited ) {
                minDuration = array.buffer[ind];
                indexOfNewMinData = ind;
                flag = true;
            }
            else if (!flag){
                if (array.buffer[ind].duration == minDuration.duration &&
                    array.buffer[ind].duration && !array.buffer[ind].visited ) {
                    minDuration = array.buffer[ind];
                    indexOfNewMinData = ind;
                    flag = true;
                }
            }
        }
        //std::cout << "Первый минимум " << ind-1;
        //    std::cout << " " << minDuration.start << " ";
        //    std::cout << " "<< minDuration.finish << " ";
        //    std::cout <<  " "<< array.buffer[ind-1].visited << " ";
        std::cout << std::endl;
        
        std::cout << "minDuration start " << minDuration.start <<" finish "<< minDuration.finish << std::endl;
        return indexOfNewMinData;
    }
    return -1;
}
