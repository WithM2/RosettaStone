// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SilenceTask.hpp>

namespace RosettaStone::SimpleTasks
{
SilenceTask::SilenceTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID SilenceTask::GetTaskID() const
{
    return TaskID::SILENCE;
}

TaskStatus SilenceTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        auto minion = dynamic_cast<Minion*>(entity);
        if (!minion)
        {
            continue;
        }

        minion->Silence();
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
