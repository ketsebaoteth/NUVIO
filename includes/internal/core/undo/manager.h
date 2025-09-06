#pragma once
#include "core/nuvio_namespaces.h"
#include <cstddef>
#include <memory>
#include <functional>
#include <string>
#include <vector>
#include "core/canvas/irenderable.h"

NUVIO_NAMESPACE_BEGIN

struct action{
  int action_id;
  std::string name;
  std::function<void(const void*)> do_func;
  std::function<void(const void*)> undo_func;
  std::shared_ptr<void> do_args;
  std::shared_ptr<void> undo_args;
  struct action* prev;
  struct action* next;
  std::vector<canvas::Irenderable> snapshot;
  
};

class UndoManager{
public:
  void add_action(action a);
  std::vector<action> get_full_history();
private:
  int max_undo_stepCount;
  std::vector<action> mHistory;

};

NUVIO_NAMESPACE_END
