#pragma once

class WorkPacket
{
  private:
    int id;

  public:
    WorkPacket(int _id);
    ~WorkPacket();
    int getId();
};