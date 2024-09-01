#include <iostream>
#include <list>

using namespace std;

// Define a structure for a free block in memory
struct FreeBlock {
    int start;  // Starting address of the free block
    int size;   // Size of the free block
};

// Function to display the current free list
void displayFreeList(list<FreeBlock>& freeList) {
    cout << "Free List: \n";
    for (const auto& block : freeList) {
        cout << "Start: " << block.start << ", Size: " << block.size << endl;
    }
}

// First-Fit Allocation
void firstFit(list<FreeBlock>& freeList, int requestedSize) {
    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if (it->size >= requestedSize) {
            cout << "Allocated at address: " << it->start << endl;
            it->start += requestedSize;
            it->size -= requestedSize;
            if (it->size == 0) {
                freeList.erase(it);  // Remove the block if no space is left
            }
            return;
        }
    }
    cout << "No sufficient free block found for size " << requestedSize << " (First-Fit)\n";
}

// Best-Fit Allocation
void bestFit(list<FreeBlock>& freeList, int requestedSize) {
    auto bestIt = freeList.end();
    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if (it->size >= requestedSize) {
            if (bestIt == freeList.end() || it->size < bestIt->size) {
                bestIt = it;
            }
        }
    }

    if (bestIt != freeList.end()) {
        cout << "Allocated at address: " << bestIt->start << endl;
        bestIt->start += requestedSize;
        bestIt->size -= requestedSize;
        if (bestIt->size == 0) {
            freeList.erase(bestIt);  // Remove the block if no space is left
        }
    } else {
        cout << "No sufficient free block found for size " << requestedSize << " (Best-Fit)\n";
    }
}

// Worst-Fit Allocation
void worstFit(list<FreeBlock>& freeList, int requestedSize) {
    auto worstIt = freeList.end();
    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if (it->size >= requestedSize) {
            if (worstIt == freeList.end() || it->size > worstIt->size) {
                worstIt = it;
            }
        }
    }

    if (worstIt != freeList.end()) {
        cout << "Allocated at address: " << worstIt->start << endl;
        worstIt->start += requestedSize;
        worstIt->size -= requestedSize;
        if (worstIt->size == 0) {
            freeList.erase(worstIt);  // Remove the block if no space is left
        }
    } else {
        cout << "No sufficient free block found for size " << requestedSize << " (Worst-Fit)\n";
    }
}

// Function to deallocate a block (merge adjacent free blocks if possible)
void deallocate(list<FreeBlock>& freeList, int start, int size) {
    auto it = freeList.begin();
    while (it != freeList.end() && it->start < start) {
        ++it;
    }

    if (it != freeList.begin() && prev(it)->start + prev(it)->size == start) {
        // Merge with previous block
        prev(it)->size += size;
        if (it != freeList.end() && prev(it)->start + prev(it)->size == it->start) {
            // Merge with next block as well
            prev(it)->size += it->size;
            freeList.erase(it);
        }
    } else if (it != freeList.end() && start + size == it->start) {
        // Merge with next block
        it->start = start;
        it->size += size;
    } else {
        // Insert new free block
        freeList.insert(it, {start, size});
    }
}

int main() {
    // Initialize free list with some blocks
    list<FreeBlock> freeList = {{0, 100}, {200, 300}, {600, 200}};

    cout << "Initial ";
    displayFreeList(freeList);

    // Perform allocations using different strategies
    firstFit(freeList, 50);
    displayFreeList(freeList);

    bestFit(freeList, 70);
    displayFreeList(freeList);

    worstFit(freeList, 100);
    displayFreeList(freeList);

    // Deallocate a block
    deallocate(freeList, 50, 50);
    cout << "After deallocation ";
    displayFreeList(freeList);

    return 0;
}
