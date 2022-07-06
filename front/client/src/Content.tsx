import './Content.css'

function Content({children} : any)
{
    return (
        <div className="content">
            {children}
        </div>
    )
}

export default Content;