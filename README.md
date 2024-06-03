# The Lost and Safe database

### An experiment in opinionated storage.

Sometimes I want to store things, but find that the "immediate access to everything" storage
paradigm works against my interests. 

I find a great paragraph while reading, and want to see it again at some point, but don't
need to encounter it on every subsequent opening of my notes app. Or I have an idea that I'd like to see again, but 
would like to let simmer for an indefinite amount of time. Or maybe I want to remember a conversation or a get-together or an experience, 
but don't need to recall it on any set schedule.

These situations call for storage with more stochastic whimsy than the usual implementation of instant, total and unlimited recall.
I made the Lost and Safe database (named in homage to [The Books](https://en.wikipedia.org/wiki/Lost_and_Safe)) to help.

The database v1 API looks like this:
	* `store(text)`: encrypts whatever text you give it.
	* `recall()`: returns something you've stored in the past. It prioritizes reverse-novelty (preferring to return things you've stored less recently),
and aims to return items with equal frequency. It is rate-limited to one retrieval per day.

Things you store here are lost: the database encrypts them on disk and will not permit fetching of any specific entry. They are also safe: whatever you store 
will come back to you eventually with enough calls to the database.

