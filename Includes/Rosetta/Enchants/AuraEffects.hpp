// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AURA_EFFECTS_HPP
#define ROSETTASTONE_AURA_EFFECTS_HPP

#include <Rosetta/Enums/CardEnums.hpp>

namespace RosettaStone
{
class Entity;

constexpr int AURA_EFFECT_CARD_SIZE = 0;
constexpr int AURA_EFFECT_WEAPON_SIZE = AURA_EFFECT_CARD_SIZE + 1;
constexpr int AURA_EFFECT_CHARACTER_SIZE = AURA_EFFECT_CARD_SIZE + 2;
constexpr int AURA_EFFECT_HERO_SIZE = AURA_EFFECT_CHARACTER_SIZE + 3;
constexpr int AURA_EFFECT_MINION_SIZE = AURA_EFFECT_CHARACTER_SIZE + 5;

//!
//! \brief AuraEffects class.
//!
//! This class is a simple container for saving tag value perturbations from
//! external auras. Call indexer to get value for a particular tag.
//!
class AuraEffects
{
 public:
    //! Constructs aura effects with given \p type.
    //! \param type The type of the card.
    explicit AuraEffects(CardType type);

    //! Destructor.
    ~AuraEffects();

    //! Deleted copy constructor.
    AuraEffects(const AuraEffects&) = delete;

    //! Deleted move constructor.
    AuraEffects(AuraEffects&&) noexcept = delete;

    //! Deleted copy assignment operator.
    AuraEffects& operator=(const AuraEffects&) = delete;

    //! Deleted move assignment operator.
    AuraEffects& operator=(AuraEffects&&) noexcept = delete;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    void SetGameTag(GameTag tag, int value);

    //! Returns the value of GameTag::IMMUNE.
    //! \return The value of GameTag::IMMUNE.
    int GetImmune() const;

    //! Sets the value of GameTag::IMMUNE.
    //! \param value The value of GameTag::IMMUNE to set.
    void SetImmune(int value);

    //! Returns the value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS.
    //! \return The value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS.
    int GetCantBeTargetedBySpells() const;

    //! Sets the value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS.
    //! \param value The value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS to set.
    void SetCantBeTargetedBySpells(int value);

    //! Returns the value of GameTag::ATK.
    //! \return The value of GameTag::ATK.
    int GetAttack() const;

    //! Sets the value of GameTag::ATK.
    //! \param value The value of GameTag::ATK to set.
    void SetAttack(int value);

    //! Returns the value of GameTag::CANNOT_ATTACK_HEROES.
    //! \return The value of GameTag::CANNOT_ATTACK_HEROES.
    int GetCannotAttackHeroes() const;

    //! Sets the value of GameTag::CANNOT_ATTACK_HEROES.
    //! \param value The value of GameTag::CANNOT_ATTACK_HEROES to set.
    void SetCannotAttackHeroes(int value);

    //! Returns the value of GameTag::HEROPOWER_DAMAGE.
    //! \return The value of GameTag::HEROPOWER_DAMAGE.
    int GetHeroPowerDamage() const;

    //! Sets the value of GameTag::HEROPOWER_DAMAGE.
    //! \param value The value of GameTag::HEROPOWER_DAMAGE to set.
    void SetHeroPowerDamage(int value);

    //! Returns the value of GameTag::HEALTH.
    //! \return The value of GameTag::HEALTH.
    int GetHealth() const;

    //! Sets the value of GameTag::HEALTH.
    //! \param value The value of GameTag::HEALTH to set.
    void SetHealth(int value);

    //! Returns the value of GameTag::CHARGE.
    //! \return The value of GameTag::CHARGE.
    int GetCharge() const;

    //! Sets the value of GameTag::CHARGE.
    //! \param value The value of GameTag::CHARGE to set.
    void SetCharge(int value);

    //! Returns the value of GameTag::TAUNT.
    //! \return The value of GameTag::TAUNT.
    int GetTaunt() const;

    //! Sets the value of GameTag::TAUNT.
    //! \param value The value of GameTag::TAUNT to set.
    void SetTaunt(int value);

    //! Returns the value of GameTag::LIFESTEAL.
    //! \return The value of GameTag::LIFESTEAL.
    int GetLifesteal() const;

    //! Sets the value of GameTag::LIFESTEAL.
    //! \param value The value of GameTag::LIFESTEAL to set.
    void SetLifesteal(int value);

    //! Returns the value of GameTag::CANT_ATTACK.
    //! \return The value of GameTag::CANT_ATTACK.
    int GetCantAttack() const;

    //! Sets the value of GameTag::CANT_ATTACK.
    //! \param value The value of GameTag::CANT_ATTACK to set.
    void SetCantAttack(int value);

 private:
    CardType m_type = CardType::INVALID;

    // Indices:
    // Cards
    // ...
    // Weapon
    // 0 : IMMUNE
    // Character
    // 1 : CANT_BE_TARGETED_BY_SPELLS / CANT_BE_TARGETED_BY_HERO_POWERS
    // 2 : ATK
    // Hero
    // 3 : CANNOT_ATTACK_HEROES
    // 4 : IMMUNE
    // 5 : HEROPOWER_DAMAGE
    // Minion
    // 3 : HEALTH
    // 4 : CHARGE
    // 5 : TAUNT
    // 6 : LIFESTEAL
    // 7 : CANT_ATTACK
    int* m_data = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_EFFECTS_HPP
