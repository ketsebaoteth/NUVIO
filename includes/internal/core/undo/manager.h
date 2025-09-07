#pragma once
#include "core/nuvio_namespaces.h"
#include <memory>
#include <vector>

NUVIO_NAMESPACE_BEGIN

class action{
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual ~action();
};

class UndoManager{
public:
  void add_action(std::unique_ptr<action> a);
  const std::vector<std::unique_ptr<action>>& get_full_history()const;
  void undo_last_action();
  void redo_last_undo();
private:
  int max_undo_stepCount;
  std::vector<std::unique_ptr<action>> mUndo;
  std::vector<std::unique_ptr<action>> mHistory;

};

extern UndoManager gUndoManager;

NUVIO_NAMESPACE_END
