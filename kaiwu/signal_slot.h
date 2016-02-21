#ifndef KW_SIGNALSLOT_H
#define KW_SIGNALSLOT_H

#include <shared_lib.h>
#include <algorithm>
#include <vector>
#include <mutex.h>
#include <ext/array_allocator.h>
#include <utility>

namespace kw {

template <typename Signature>
class Signal;

template <typename Signature>
class SlotImpl;

typedef kw::shared_ptr<void> SlotHandle;

template <typename Signature>
class SignalImpl
{
public:
    typedef typename kw::SlotImpl<Signature>	SlotObj;
    typedef typename kw::weak_ptr<SlotObj> 		SlotWeakPtr;
    typedef kw::function<Signature>				SlotFunc;

    SignalImpl()
        :slots_(new std::vector<SlotWeakPtr>())
    {}

    kw::shared_ptr<std::vector<SlotWeakPtr> > GetSlots()
    {
        MutexGuard lock(mutex_);
        return slots_;
    }

    void AddSlot(kw::shared_ptr<SlotObj>& slot_obj)
    {
        MutexGuard lock(mutex_);

        //copy while reading
        if(!slots_.unique())
            slots_.reset(new std::vector<SlotWeakPtr>(*slots_));

        slots_->push_back(slot_obj);
    }

    void Clean()
    {
        MutexGuard lock(mutex_);

        //copy while reading
        if(!slots_.unique())
            slots_.reset(new std::vector<SlotWeakPtr>(*slots_));

        typename std::vector<SlotWeakPtr>::iterator iter = slots_->begin();
        while(slots_->end() != iter)
        {
            SlotWeakPtr& slot_weak_ptr = *iter;

            if(!slot_weak_ptr.expired())
            {
                ++iter;
                continue;
            }

            slots_->erase(iter);
        }
    }

private:
    kw::shared_ptr<std::vector<SlotWeakPtr> > slots_;
    kw::Mutex mutex_;
};

template <typename Signature>
class SlotImpl
{
public:
    typedef kw::function<Signature>	SlotFunc;

    SlotImpl(SlotFunc slot_func, kw::shared_ptr<SignalImpl<Signature> >& signal)
        :slot_func_(slot_func), signal_(signal)
    {
    }

    ~SlotImpl()
    {
        kw::shared_ptr<SignalImpl<Signature> > signal_ptr(signal_.lock());
        if(!signal_ptr)
            return;

        //fixed:can erase exactly?
        signal_ptr->Clean();
    }

    template<typename... ArgTypes>
    void Call(ArgTypes... args)
    {
        slot_func_(args...);
    }

private:
   SlotFunc slot_func_;
   typename Signal<Signature>::ConnectType connect_type_;
   kw::weak_ptr<SignalImpl<Signature> > signal_;
};

template<typename Ret, typename... ArgTypes>
class Signal<Ret(ArgTypes...)>
{
public:
    enum ConnectType
    {
        CT_AUTO, CT_DIRECT, CT_QUEUE, CT_BLOCKINGQUEUE
    };

    typedef SlotImpl<Ret(ArgTypes...)> 		SlotImplType;
    typedef SignalImpl<Ret(ArgTypes...)> 	SignalImplType;

    Signal()
        :signal_impl_(new SignalImplType())
    {
    }

    ~Signal()
    {
    }

    SlotHandle Connect(typename SlotImplType::SlotFunc slot_fun)
    {
        kw::shared_ptr<SlotImplType> slot_func(new SlotImplType(slot_fun, signal_impl_));

        signal_impl_->AddSlot(slot_func);

        return slot_func;
    }

    void Emit(ArgTypes... args)
    {
        //lock and return the locks
        kw::shared_ptr<std::vector<typename SignalImplType::SlotWeakPtr> > slots = signal_impl_->GetSlots();

        typename std::vector<typename SignalImplType::SlotWeakPtr>::iterator iter = slots->begin();

        for(; slots->end() != iter; ++iter)
        {
            typename SignalImplType::SlotWeakPtr& slot_weak_ptr = *iter;
            kw::shared_ptr<typename SignalImplType::SlotObj> slot_ptr = slot_weak_ptr.lock();

            if(!slot_ptr)
                continue;

            slot_ptr->Call(args...);
        }
    }

private:
    kw::shared_ptr<SignalImplType> signal_impl_;
};

}
#endif // KW_SIGNALSLOT_H
