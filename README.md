# The Lost and Safe database

### An experiment in opinionated storage

Sometimes I want to store things, but find that the "immediate access to everything" storage
paradigm works against my interests. 

Maybe I read a great paragraph and immediately want to see it again at some point, but don't
want to encounter it on every subsequent opening of my notes app. Or maybe I have an idea that I'd like to see again
after it simmers for some indefinite amount of time. Perhaps I want to remember a conversation or an experience, 
but might prefer to wait awhile before re-encountering it.

These situations call for storage with a little more stochastic whimsy.
I made the Lost and Safe database (homage to [The Books](https://en.wikipedia.org/wiki/Lost_and_Safe)) to help.

Things you store here are lost: the database will not permit fetching of any specific entry. They are also safe: whatever you store 
will come back to you eventually with enough calls to the database.

### Usage

LSDB v1 is a simple CLI app: 

* `lsdb store '<text>'` serializes text input to local storage.

```
~ lsdb store 'A recipe idea, or a phone number, or whatever else'
Successfully stored: A recipe idea, or a phone number, or whatever else
```



* `lsdb recall` returns something you've stored in the past. It prioritizes reverse-novelty (preferring to return things you've stored less recently),
and items that have been returned less often.

```
~ lsdb recall

A recipe idea, or a phone number, or whatever else

Last seen on: Sun Nov 10 11:59:21 2024 EST
Surfaced 0 times previously
```

LSDB v2 (in progress!) will encrypt input to provide an extra measure of lost-ness, and rate-limit retrievals. It may eventually evolve to a web app.

### Building
Create a build directory within the project. From the build directory, run `cmake --build .`

### Installing
From your build directory, run `cmake --install .`