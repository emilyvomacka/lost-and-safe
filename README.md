# The Lost and Safe database

### An experiment in opinionated storage

**NOTE:** in active development (nothing works yet)

Sometimes I want to store things, but find that the "immediate access to everything" storage
paradigm works against my interests. 

Maybe I read a great paragraph and immediately want to see it again at some point, but don't
want to encounter it on every subsequent opening of my notes app until it becomes meaningless digital wallpaper. Or maybe I have an idea that I'd like to see again
after it simmers for some indefinite amount of time. Perhaps I want to remember a conversation or a get-together or an experience, 
but don't need to recall it at any specific moment and might actually prefer to wait awhile before re-encountering it.

These situations call for storage with more stochastic whimsy than the usual implementation of instant, total and unlimited recall.
I made the Lost and Safe database (named in homage to [The Books](https://en.wikipedia.org/wiki/Lost_and_Safe)) to help.

The database v1 API looks like this:

* `store(text)` encrypts and serializes whatever text you give it.
* `recall()` returns something you've stored in the past. It prioritizes reverse-novelty (preferring to return things you've stored less recently),
and returns items with equal frequency. It is rate-limited to one retrieval per day.

Things you store here are lost: the database encrypts them on disk and will not permit fetching of any specific entry. They are also safe: whatever you store 
will come back to you eventually with enough calls to the database. 

