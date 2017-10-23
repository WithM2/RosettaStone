/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/GameAgent.h>

namespace Hearthstonepp
{
	User::User(Player *player, int deckID)
	{
		Cards *cards = Cards::GetInstance();

		Deck *tmpDeck = player->GetDeck(deckID);
		CardClass cardclass = tmpDeck->GetClass();

		const Card *hero = cards->FindCardByID(std::move(ConvertFromCardClassToHeroID.at(cardclass)));
		const Card *power = cards->FindCardByID(std::move(ConvertFromCardClassToHeroPowerID.at(cardclass)));

		this->player = player;
		this->deck = tmpDeck->GetPrimitiveDeck();
		this->hero = static_cast<Hero*>(const_cast<Card*>(hero));
		this->power = static_cast<HeroPower*>(const_cast<Card*>(power));
		this->weapon = nullptr;
	}

	GameAgent::GameAgent(User& user1, User& user2, int maxBufferSize)
		: userCurrent(user1)
		, userOpponent(user2)
		, inBuffer(maxBufferSize) // initialize pipe buffer
		, outBuffer(maxBufferSize)
		, generator(rd()) // initialize random generator
	{
		// Do Nothing
	}

	GameAgent::GameAgent(User&& user1, User&& user2, int maxBufferSize)
		: userCurrent(std::move(user1))
		, userOpponent(std::move(user2))
		, inBuffer(maxBufferSize) // initialize pipe buffer
		, outBuffer(maxBufferSize)
		, generator(rd()) // initialize random generator
	{
		// Do Nothing
	}

	std::thread* GameAgent::StartAgent(GameResult& result)
	{
		std::thread *agent = new std::thread([this](GameResult& result) {
			BeginPhase();

			while (!IsGameEnd())
			{
				MainPhase();
			}

			FinalPhase(result);
		}, std::ref(result));

		return agent; // return new GameAgent thread
	}

	void GameAgent::BeginPhase()
	{
		// userCurrent : user who start first
		// userOpponent : user who start later
		DecideDeckOrder();

		ShuffleDeck(userCurrent);
		ShuffleDeck(userOpponent);

		Draw(userCurrent, 3);
		Draw(userOpponent, 3);

		Mulligan(userCurrent);
		Mulligan(userOpponent);

		userOpponent.hand.push_back(new Card()); // Coin for later user
	}

	void GameAgent::MainPhase()
	{

	}

	void GameAgent::FinalPhase(GameResult& result)
	{

	}

	void GameAgent::DecideDeckOrder()
	{
		// get random number, zero or one.
		std::uniform_int_distribution<int> bin(0, 1);
		if (bin(generator) == 1) // swap user with 50% probability
		{
			std::swap(userCurrent, userOpponent);
		}
	}

	void GameAgent::ShuffleDeck(User& user)
	{
		std::vector<Card*>& deck = user.deck;
		std::shuffle(deck.begin(), deck.end(), generator); // shuffle with random generator
	}

	void GameAgent::Mulligan(User& user)
	{
		BYTE index[3] = { 0, };
		std::vector<Card*>& hand = user.hand;

		WriteOutputBuffer((BYTE*)hand.data(), sizeof(Card*) * 3); // send card data to user
		int read = ReadInputBuffer(index, 3); // read index of the card to be mulligan

		std::sort(index, index + read, std::greater<int>());
		for (int i = 0; i < read; ++i)
		{
			hand.erase(hand.begin() + index[i]); // erase card with given index
		}

		Draw(user, read);

		WriteOutputBuffer((BYTE*)hand.data(), sizeof(Card*) * 3); // send new card data
	}

	bool GameAgent::IsGameEnd()
	{
		return true;
		/*
		int healthCurrent = userCurrent.hero->health;
		int healthOpponent = userOpponent.hero->health;

		if (healthCurrent <= 0 || healthOpponent <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		*/
	}

	void GameAgent::Draw(User& user, int num)
	{
		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		for (int i = 0; i < num; ++i)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}
	}

	int GameAgent::ReadBuffer(BYTE *arr, int maxSize)
	{
		return outBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteBuffer(BYTE *arr, int size)
	{
		return inBuffer.WriteBuffer(arr, size);
	}

	int GameAgent::ReadInputBuffer(BYTE* arr, int maxSize)
	{
		return inBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteOutputBuffer(BYTE* arr, int size)
	{
		return outBuffer.WriteBuffer(arr, size);
	}
}