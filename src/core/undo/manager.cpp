#include "core/undo/manager.h"
#include "core/nuvio_namespaces.h"
#include <memory>

NUVIO_NAMESPACE_BEGIN

void UndoManager::add_action(std::unique_ptr<action> a){mHistory.push_back(std::move(a));}
action::~action(){};

const std::vector<std::unique_ptr<action>>& UndoManager::get_full_history() const {
  return mHistory;
}

void UndoManager::undo_last_action(){
  if(!mHistory.empty()){
    auto last = std::move(mHistory.back());
    last->undo();
    mUndo.push_back(std::move(last));
    mHistory.pop_back();
  }
}

void UndoManager::redo_last_undo(){
  if(!mUndo.empty()){
    auto last = std::move(mUndo.back());
    last->execute();
    mHistory.push_back(std::move(last));
    mUndo.pop_back();
  }
}

UndoManager gUndoManager;

NUVIO_NAMESPACE_END
