%% views/header.html %%
<h1>{{$title}}</h1>
<ul>
    [[ foreach($users as $user) : ]]
    <li><a href='@@users/view/{{$user->getId()}}@@'>[View]</a> <a href='@@users/groups/{{$user->getId()}}@@'>[Groups]</a> <a href='@@users/delete/{{$user->getId()}}@@'>[Delete]</a> {{$user->getFullName()}}</li>
    [[ endforeach; ]]
</ul>
%% views/footer.html %%
