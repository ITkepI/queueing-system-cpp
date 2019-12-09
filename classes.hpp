//
//  classes.hpp
//  myProject
//
//  Created by Nick Sobolev on 09.12.2019.
//  Copyright © 2019 Nick Sobolev. All rights reserved.
//

#ifndef classes_hpp
#define classes_hpp

struct BufferInf {
  int threadNum;
  double requestTime;
};

class Generator {
public:
  Generator(int, int, int);
  double getDeviceLambda() const;
  void initNewIteration();
  double getTimeInterval(int) const;
private:
  const double MAX_DEVICE_LAMBDA_;
  const double DIFFERENCE_BETWEEN_DEVICE_LAMBDA_;
  double deviceLambda_;
};

class Buffer {
public:
  Buffer();
  BufferInf readBufferElem_;
protected:
  void write();
  void read();
};

class QueueingSystem {
public:
  QueueingSystem(int);
  void modeling();
private:
  const int THREAD_NUM_;
  double deviceTime;
  double threadTime_[THREAD_NUM_];
};

class SimulationResult {
public:
  SimulationResult(int, int);
  double getProbabilityOfFail();
  double getWaitingBufferTime();
  double getDeviceDowntime();
private:
  const int THREAD_NUM_;
  const int MIN_NUM_OF_ITERATION;
  int numOfRequest[THREAD_NUM_];
  int numOfProcessedRequests[THREAD_NUM_];
  int numOfDeniedRequests[THREAD_NUM_];
  double probabilityOfFail[THREAD_NUM_];
  double waitingBufferTime[THREAD_NUM_]; //Время ожидания заявки в буфере
  double deviceDowntime; //Время простоя прибора
};

#endif /* classes_hpp */
