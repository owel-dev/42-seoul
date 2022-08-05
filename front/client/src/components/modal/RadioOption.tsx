function RadioOption(props: { radioChange: Function; value: string }) {
  return (
    <div>
      <input
        type='radio'
        name='drone'
        id={props.value}
        value={props.value}
        onChange={() => props.radioChange(props.value)}
      ></input>
      <label>{props.value}</label>
    </div>
  );
}

export default RadioOption;
