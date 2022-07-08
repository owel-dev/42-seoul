import {useState, useEffect} from 'react';
import axios from 'axios';
import 'styles/mypage/MatchTable.css'
import {matchList} from 'types/MyPageTypes'

// const dummy = {
//     matchList:
//         [
//             {
//                 player1 : "hello",
//                 player2 : "bye",
//                 playerScore1 : 7,
//                 playerScore2 : 4
//             },
//             {
//                 player1 : "hello",
//                 player2 : "zzz",
//                 playerScore1 : 6,
//                 playerScore2 : 5
//             },
//             {
//                 player1 : "hello",
//                 player2 : "qapla",
//                 playerScore1 : 2,
//                 playerScore2 : 9
//             }
//         ]
// };


const id : string = "hello";//임시값

function MatchTable(){
    const [List, setList] = useState<matchList | null>(null);
    useEffect(() => {
        const fetchData = async () => {
            try {
                const getAPI = await axios.get(
                    'http://localhost:3000/users/' + {id} + '/match', {
                    headers: {
                        'Content-Type': 'application/json'
                    }
                });
                setList(getAPI.data);
            } catch (e) {
                console.log(e);
            }
        };
        fetchData();
    }, []);

    return (
        <div className='match-table'>
            {List?.matchList.map((element, index) => {
                return (
                    <div className='match-row' key={index}>
                        <span>{element.player1} </span>
                        <span>{element.playerScore1}</span>
                        <span> vs </span>
                        <span>{element.player2} </span>
                        <span>{element.playerScore2}</span>
                    </div>
                );
            })}
            
        </div>
    );
}
export default MatchTable;